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

#include <libmedusa/ARMv7Machine.hpp>
#include <libmedusa/libmedusa.hpp>

using namespace std;

int main(int argc, char *argv[]) {
	libmedusa::ARMv7Machine armv7_machine;
	libmedusa::mem_reg_t	region;
	region.addr = 0x0;
	region.size = 0x10000;
	region.prot = XP_PROT_READ | XP_PROT_WRITE | XP_PROT_EXEC;
	armv7_machine.map_memory(region);

	vector<uint8_t> assembled = armv7_machine.assemble("mov r0, #0x41\nmov r1, r0\n", 0, 0);
	armv7_machine.write_memory(0, assembled);

	for (uint8_t& i: assembled) {
		printf("%02x", i);
	}

	printf("\n");

	libmedusa::reg_t reg;
	reg.reg_name		= "pc";
	reg.reg_description = "pc";
	reg.reg_id			= 0xf;
	reg.reg_value		= 0x0;

	armv7_machine.set_register(reg);

	for (int i = 0; i < 0x8; i++) {
		vector<libmedusa::reg_t> registers = armv7_machine.get_registers();

		for (libmedusa::reg_t& i: registers) {
			printf("%s %s %lx %lx\n", i.reg_name.c_str(), i.reg_description.c_str(), i.reg_id, i.reg_value);
		}

		armv7_machine.exec_code_step();
	}

	return 0;
}