/*
 *  Copyright (C) 2022, w212 research. <contact@w212research.com>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of version 2 of the GNU General Public License as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <libmedusa/ExampleDisplayComponent.hpp>
#include <libmedusa/ExampleComponent2.hpp>
#include <libmedusa/ExampleComponent.hpp>
#include <libmedusa/DisplayOutput.hpp>
#include <libmedusa/ARMv7Machine.hpp>
#include <libmedusa/ARM64Machine.hpp>
#include <libmedusa/Component.hpp>
#include <libmedusa/libmedusa.hpp>
#include <capstone/capstone.h>
#include <unicorn/unicorn.h>
#include <LIEF/LIEF.hpp>
#include <cstdio>
#include <vector>

using namespace std;

#define BASE_ADDY 0x0

uc_engine* uc_global;

uint8_t test_arm_code[] = {
	0x00, 0x00, 0xA0, 0xE1,
	0x41, 0x00, 0xB0, 0xE3,
	0x20, 0x04, 0x00, 0xE3,
	0x69, 0x10, 0x00, 0xE3,
	0x01, 0x00, 0x40, 0xE0,
	0x00, 0x10, 0x81, 0xE0,
	0x00, 0x00, 0xA0, 0xE1,
};

uint8_t test_arm_thumb_code[] = {
	0x41, 0x20,						//	movs	r0,	#0x41
	0x40, 0xF2, 0x20, 0x40,			//	movw	r0,	#0x420
	0x40, 0xF2, 0x69, 0x01,			//	movw	r1,	#0x69
	0xA0, 0xEB, 0x01, 0x00,			//	sub		r0,	r0,	r1
	0x01, 0x44,						//	add		r1,	r1,	r0
	0x00, 0x00,						//  mov		r0,	r0
};

uint8_t test_arm64_code[] = {
	0x20, 0x28, 0x88, 0xD2,
	0x41, 0x48, 0x88, 0xD2,
	0x02, 0x00, 0x01, 0x8B,
	0xE3, 0x03, 0x02, 0xAA,
};

uint8_t test_arm64_code2[] = {
	0xd2, 0x88, 0x28, 0x20,
	0x8b, 0x01, 0x00, 0x02,
	0xd2, 0x88, 0x48, 0x41,
	0xaa, 0x02, 0x03, 0xe3,
};

void generic_machine_demo(libmedusa::Machine& generic_machine) {
	libmedusa::reg_t reg;

	reg.reg_description = "pc";
	reg.reg_name = "pc";
	reg.reg_id = 15;
	reg.reg_value = 0x1;

	generic_machine.set_register(reg);

	reg.reg_description = "pc";
	reg.reg_name = "pc";
	reg.reg_id = 0x1f;
	reg.reg_value = 0x0;

	generic_machine.set_register(reg);

	for (int i = 0; i < 0x10; i++) {
		vector<libmedusa::reg_t> registers = generic_machine.get_registers();
		for (libmedusa::reg_t& i : registers) {
			printf("%s %s %lx %lx\n", i.reg_description.c_str(), i.reg_name.c_str(), i.reg_id, i.reg_value);
		}

		generic_machine.step_instruction();
	}
}

const int BYTES_PER_PIXEL = 3; /// red, green, & blue
const int FILE_HEADER_SIZE = 14;
const int INFO_HEADER_SIZE = 40;

/*
 *  BEGIN stolen code from stackoverflow
 */
void generate_bitmap_image(unsigned char* image, int height, int width, char* image_file_name);
unsigned char* create_bitmap_file_header(int height, int stride);
unsigned char* create_bitmap_info_header(int height, int width);

void generate_bitmap_image(unsigned char* image, int height, int width, char* image_file_name) {
	int width_in_bytes = width * BYTES_PER_PIXEL;

	unsigned char padding[3] = {0, 0, 0};
	int padding_size = (4 - (width_in_bytes) % 4) % 4;

	int stride = (width_in_bytes) + padding_size;

	FILE* image_file = fopen(image_file_name, "wb");

	unsigned char* file_header = create_bitmap_file_header(height, stride);
	fwrite(file_header, 1, FILE_HEADER_SIZE, image_file);

	unsigned char* info_header = create_bitmap_info_header(height, width);
	fwrite(info_header, 1, INFO_HEADER_SIZE, image_file);

	int i;
	for (i = 0; i < height; i++) {
		fwrite(image + (i * width_in_bytes), BYTES_PER_PIXEL, width, image_file);
		fwrite(padding, 1, padding_size, image_file);
	}

	fclose(image_file);
}

unsigned char* create_bitmap_file_header(int height, int stride) {
	int file_size = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (stride * height);

	static unsigned char file_header[] = {
		0,0,     /// signature
		0,0,0,0, /// image file size in bytes
		0,0,0,0, /// reserved
		0,0,0,0, /// start of pixel array
	};

	file_header[ 0] = (unsigned char)('B');
	file_header[ 1] = (unsigned char)('M');
	file_header[ 2] = (unsigned char)(file_size      );
	file_header[ 3] = (unsigned char)(file_size >>  8);
	file_header[ 4] = (unsigned char)(file_size >> 16);
	file_header[ 5] = (unsigned char)(file_size >> 24);
	file_header[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);

	return file_header;
}

unsigned char* create_bitmap_info_header(int height, int width) {
	static unsigned char info_header[] = {
		0,0,0,0, /// header size
		0,0,0,0, /// image width
		0,0,0,0, /// image height
		0,0,     /// number of color planes
		0,0,     /// bits per pixel
		0,0,0,0, /// compression
		0,0,0,0, /// image size
		0,0,0,0, /// horizontal resolution
		0,0,0,0, /// vertical resolution
		0,0,0,0, /// colors in color table
		0,0,0,0, /// important color count
	};

	info_header[ 0] = (unsigned char)(INFO_HEADER_SIZE);
	info_header[ 4] = (unsigned char)(width      );
	info_header[ 5] = (unsigned char)(width  >>  8);
	info_header[ 6] = (unsigned char)(width  >> 16);
	info_header[ 7] = (unsigned char)(width  >> 24);
	info_header[ 8] = (unsigned char)(height      );
	info_header[ 9] = (unsigned char)(height >>  8);
	info_header[10] = (unsigned char)(height >> 16);
	info_header[11] = (unsigned char)(height >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(BYTES_PER_PIXEL*8);

	return info_header;
}

/*
 *  END stolen code from stackoverflow
 */

void handle_example_component(libmedusa::ExampleComponent& component) {
	printf("%d\n", component.get_component_int_output());
}

void handle_example_component2(libmedusa::ExampleComponent2& component) {
	printf("%s\n", component.get_component_string_output().c_str());
}

void handle_display_component(libmedusa::DisplayOutput& component) {
	libmedusa::bitmap_t bitmap = component.get_component_display_output();

	generate_bitmap_image((unsigned char*)bitmap.pixels, bitmap.height, bitmap.width, "bin/out.bmp");
}

void handle_component(libmedusa::Component& component) {
	libmedusa::component_definition_t component_definition;
	component_definition = component.get_component_definition();

	printf("%s %s 0x%lx 0x%lx\n",
		   component_definition.name.c_str(),
		   component_definition.description.c_str(),
		   component_definition.component_type,
		   component_definition.component_id);
	
	if (component_definition.component_type == EXAMPLE_COMPONENT_TYPE) {
		handle_example_component((libmedusa::ExampleComponent&)component);
	}
	
	if (component_definition.component_type == EXAMPLE_COMPONENT2_TYPE) {
		handle_example_component2((libmedusa::ExampleComponent2&)component);
	}
	
	if (component_definition.component_type == DISPLAY_COMPONENT_TYPE) {
		handle_display_component((libmedusa::DisplayOutput&)component);
	}
}

int main(int argc, char* argv[]) {
	libmedusa::ARMv7Machine armv7_machine;

	vector<libmedusa::mem_reg_t> memory_regions = armv7_machine.get_memory_regions();
	for (libmedusa::mem_reg_t& i : memory_regions) {
		printf("%lx %lx %lx\n", i.addr, i.size, i.prot);
	}

	libmedusa::mem_reg_t region;

	region.addr = 0x0;
	region.size = 0x10000;
	region.prot = XP_PROT_READ | XP_PROT_WRITE | XP_PROT_EXEC;

	printf("map\n");
	armv7_machine.map_memory(region);

	memory_regions = armv7_machine.get_memory_regions();
	for (libmedusa::mem_reg_t& i : memory_regions) {
		printf("%lx %lx %lx\n", i.addr, i.size, i.prot);
	}

	vector<libmedusa::reg_t> registers = armv7_machine.get_registers();
	for (libmedusa::reg_t& i : registers) {
//		printf("%s %s %lx %lx\n", i.reg_description.c_str(), i.reg_name.c_str(), i.reg_id, i.reg_value);
	}

	vector<uint8_t> data;
	vector<uint8_t> test_arm_thumb_code_vector(test_arm_thumb_code, test_arm_thumb_code + sizeof(test_arm_thumb_code));

	armv7_machine.write_memory(0, test_arm_thumb_code_vector);
	data = armv7_machine.read_memory(0, sizeof(test_arm_thumb_code));

	for (int i = 0; i < sizeof(test_arm_thumb_code); i++) {
		printf("%02x", data[i]);
	}
	printf("\n");

	registers = armv7_machine.get_registers();
	for (libmedusa::reg_t& i : registers) {
//		printf("%s %s %lx %lx\n", i.reg_description.c_str(), i.reg_name.c_str(), i.reg_id, i.reg_value);
	}

	libmedusa::reg_t reg;
	reg.reg_description = "r0";
	reg.reg_name = "r0";
	reg.reg_id = 0;
	reg.reg_value = 0x7777;

	armv7_machine.set_register(reg);

	registers = armv7_machine.get_registers();
	for (libmedusa::reg_t& i : registers) {
//		printf("%s %s %lx %lx\n", i.reg_description.c_str(), i.reg_name.c_str(), i.reg_id, i.reg_value);
	}

	printf("%d\n", __LINE__);
	armv7_machine.exec_code_step();
	printf("%d\n", __LINE__);
	armv7_machine.exec_code_step();
	printf("%d\n", __LINE__);
	armv7_machine.exec_code_addr_ninsns(1, 1);
	printf("%d\n", __LINE__);
	armv7_machine.exec_code_step();
	printf("%d\n", __LINE__);
	armv7_machine.exec_code_step();
	printf("%d\n", __LINE__);

	for (int i = 0; i < 0x8; i++) {
		armv7_machine.exec_code_step();

		registers = armv7_machine.get_registers();
		for (libmedusa::reg_t& i : registers) {
//			printf("%s %s %lx %lx\n", i.reg_description.c_str(), i.reg_name.c_str(), i.reg_id, i.reg_value);
		}
	}

	data = armv7_machine.read_memory(0, sizeof(test_arm_thumb_code));
	vector<libmedusa::insn_t> disas = armv7_machine.disassemble(data, XP_FLAG_THUMB);

	for (libmedusa::insn_t& i : disas) {
		printf("%016lx (%04x): %s %s\n", i.address, i.size, i.mnemonic, i.op_str);
	}

	std::vector<uint8_t> assembled = armv7_machine.assemble("mov r0, #0x41\nmov r0, r0\n", 0, XP_FLAG_THUMB);

	printf("assembled\n");

	disas = armv7_machine.disassemble(assembled, XP_FLAG_THUMB);

	for (libmedusa::insn_t& i : disas) {
		printf("%016lx (%04x): %s %s\n", i.address, i.size, i.mnemonic, i.op_str);
	}

	libmedusa::ARM64Machine arm64_machine;

	region.addr = 0x0;
	region.size = 0x10000;
	region.prot = XP_PROT_READ | XP_PROT_WRITE | XP_PROT_EXEC;

	printf("map\n");
	arm64_machine.map_memory(region);

	vector<uint8_t> test_arm64_code_vector(test_arm64_code, test_arm64_code + sizeof(test_arm64_code));

	arm64_machine.write_memory(0, test_arm64_code_vector);
	data = arm64_machine.read_memory(0, sizeof(test_arm64_code));

	for (int i = 0; i < sizeof(test_arm64_code); i++) {
		printf("%02x", data[i]);
	}
	printf("\n");

	reg.reg_description = "pc";
	reg.reg_name = "pc";
	reg.reg_id = 0x1f;
	reg.reg_value = 0x0;

	arm64_machine.set_register(reg);

	for (int i = 0; i < 0x8; i++) {
		arm64_machine.exec_code_step();

		registers = arm64_machine.get_registers();
		for (libmedusa::reg_t& i : registers) {
			printf("%s %s %lx %lx\n", i.reg_description.c_str(), i.reg_name.c_str(), i.reg_id, i.reg_value);
		}
	}

	printf("-------\n");
	libmedusa::ARMv7Machine armv7_machine1;
	libmedusa::ARM64Machine arm64_machine1;

	region.addr = 0x0;
	region.size = 0x10000;
	region.prot = XP_PROT_READ | XP_PROT_WRITE | XP_PROT_EXEC;

	armv7_machine1.map_memory(region);

	vector<uint8_t> code_vector(test_arm_thumb_code,
								test_arm_thumb_code + sizeof(test_arm_thumb_code));

	armv7_machine1.write_memory(0, code_vector);

	region.addr = 0x0;
	region.size = 0x10000;
	region.prot = XP_PROT_READ | XP_PROT_WRITE | XP_PROT_EXEC;

	arm64_machine1.map_memory(region);

	vector<uint8_t> code_vector2(test_arm64_code,
								test_arm64_code + sizeof(test_arm64_code));

	arm64_machine1.write_memory(0, code_vector2);
	generic_machine_demo(armv7_machine1);
	printf("-------\n");
	generic_machine_demo(arm64_machine1);

	libmedusa::ExampleComponent example_component;
	libmedusa::ExampleComponent2 example_component2;
	libmedusa::ExampleDisplayComponent display_component;

	handle_component(example_component);
	handle_component(example_component);
	handle_component(example_component);
	handle_component(example_component);
	handle_component(example_component);

	handle_component(example_component2);
	handle_component(example_component2);
	handle_component(example_component2);
	handle_component(example_component2);
	handle_component(example_component2);

	handle_component(display_component);

	return 0;
}