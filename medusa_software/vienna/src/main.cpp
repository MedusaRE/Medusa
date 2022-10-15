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
#include <vienna/ARMv7Decompiler.hpp>
#include <libmedusa/libmedusa.hpp>
#include <vienna/vienna.hpp>
#include <cstdio>

static uint8_t test_arm_code[] = {
	0x20, 0x04, 0x00, 0xE3,
	0x69, 0x10, 0x00, 0xE3,
	0x01, 0x00, 0x40, 0xE0,
	0x00, 0x10, 0x81, 0xE0,
	0x01, 0x01, 0x90, 0xE7,
	0x02, 0x00, 0x81, 0xE0,
	0x00, 0x30, 0xA0, 0xE1,
	0x90, 0x01, 0x00, 0xE0,
	0x91, 0x02, 0x00, 0xE0,
	0x01, 0x00, 0x50, 0xE1,
	0x0E, 0x00, 0x00, 0xDB,
};

int main(int argc, char* argv[]) {
	printf("Hello, world!\n");

	std::vector<uint8_t> machine_code(test_arm_code,
									  test_arm_code + sizeof(test_arm_code));
	printf("%s\n", vienna::decompile_armv7(machine_code).c_str());

	return 0;
}
