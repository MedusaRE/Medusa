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

#include <libmedusa/ARMv7Machine.hpp>
#include <libmedusa/libmedusa.hpp>
#include <libmedusa/Machine.hpp>
#include <vienna/vienna.hpp>
#include <cstdio>
#include <vector>

using namespace vienna;

static uint8_t test_arm_code[] = {
	0x00, 0x00, 0xA0, 0xE1,
	0x41, 0x00, 0xB0, 0xE3,
	0x20, 0x04, 0x00, 0xE3,
	0x69, 0x10, 0x00, 0xE3,
	0x01, 0x00, 0x40, 0xE0,
	0x00, 0x10, 0x81, 0xE0,
	0x00, 0x00, 0xA0, 0xE1,
};

void vienna::test_function(void) {
	printf("vienna::test_function test printf\n");

	libmedusa::ARMv7Machine armv7_machine;
	std::vector<uint8_t> tmp_vector(test_arm_code, test_arm_code + sizeof(test_arm_code));
	std::vector<libmedusa::insn_t> insns = armv7_machine.disassemble(tmp_vector, 0);

	for (int i = 0; i < insns.size(); i++) {
		printf("0x%016lx (%d): %s %s\n", insns[i].address, insns[i].size, insns[i].mnemonic, insns[i].op_str);
	}
}
