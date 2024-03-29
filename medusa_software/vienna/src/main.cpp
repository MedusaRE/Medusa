/*
 *  Copyright (C) 2023, w212 research. <contact@w212research.com>
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

#include <cstdio>
#include <cstring>
#include <fstream>
#include <lib.h>
#include <libmedusa/ARMv7Machine.hpp>
#include <libmedusa/libmedusa.hpp>
#include <sys/mman.h>
#include <vienna/ARMv7Decompiler.hpp>
#include <vienna/vienna.hpp>

using namespace std;

static uint8_t test_arm_code[] = {
	0x20, 0x04, 0x00, 0xE3, 0x69, 0x10, 0x00, 0xE3, 0x01, 0x00, 0x40,
	0xE0, 0x00, 0x10, 0x81, 0xE0, 0x01, 0x01, 0x90, 0xE7, 0x02, 0x00,
	0x81, 0xE0, 0x00, 0x30, 0xA0, 0xE1, 0x90, 0x01, 0x00, 0xE0, 0x91,
	0x02, 0x00, 0xE0, 0x01, 0x00, 0x50, 0xE1, 0x0E, 0x00, 0x00, 0xDB,
};

static uint8_t test_arm_code2[] = {
	0x40, 0x00, 0x00, 0xE3, 0x00, 0x00, 0x40, 0xE3, 0x00, 0x10, 0x90,
	0xE5, 0x01, 0x10, 0x81, 0xE2, 0x00, 0x10, 0x80, 0xE5, 0x01, 0x2C,
	0xA0, 0xE3, 0x02, 0x00, 0x51, 0xE1, 0xF7, 0xFF, 0xFF, 0x1A,
};

int main(int argc, char *argv[]) {
	printf("Hello, world!\n");
	ifstream f("res/bin/armv7_ls.bin", ios::binary);

#define MB_SIZE		(1048576 * 16)
#define BUF_TO_COPY test_arm_code2

#if 0
	uint8_t* MB_of_code = (uint8_t*)calloc(MB_SIZE, 1);

	for (size_t i = 0; i < (MB_SIZE / sizeof(BUF_TO_COPY)); i++) {
		memcpy(MB_of_code + (i * sizeof(BUF_TO_COPY)), BUF_TO_COPY, sizeof(BUF_TO_COPY));
	}

	std::vector<uint8_t> machine_code(MB_of_code,
									  MB_of_code + MB_SIZE);
#else
	//	std::vector<uint8_t> machine_code((std::istreambuf_iterator<char>(f)),
	//  std::istreambuf_iterator<char>());
	std::vector<uint8_t> machine_code(BUF_TO_COPY, BUF_TO_COPY + sizeof(BUF_TO_COPY));

	printf("%s\n", vienna::decompile_armv7(machine_code).c_str());
	return 0;
#endif

	DEBUG_INFO();
	for (int i = 0; i < 0x10; i++) {
		fprintf(stderr, "\n");
		fprintf(stderr, "--------------------------------------------------------------------------------\n");
		printf("%s\n", vienna::decompile_armv7(machine_code).c_str());
		DEBUG_INFO();
	}

	return 0;
}
