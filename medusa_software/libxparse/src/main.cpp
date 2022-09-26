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

#include "XParse.hpp"
#include <cstdint>
#include <cstring>
#include <fstream>
#include "ELF.hpp"
#include <cstdio>
#include <vector>
#include "lib.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc == 1) {
		fprintf(stderr, "usage: %s (path to binary)\n", argv[0]);
		return -1;
	} else if (argc == 0) {
		fprintf(stderr, "usage: xparse (path to binary)\n");
		return -1;
	}

	printf("%x %x %lx\n",
		   U8X2_TO_U16(0x41, 0x42),
		   U8X4_TO_U32(0x41, 0x42, 0x43, 0x44),
		   U8X8_TO_U64(0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48));

	ifstream f(argv[1], ios::binary);
	vector<uint8_t> buf(istreambuf_iterator<char>(f), {});
	XParse::format_t format;

	f.close();

	format = XParse::detect_format(buf);
	printf("%d\n", format);

	XParse::ELF::raw_elf_file_header_t file_header = XParse::ELF::parse_elf_binary_raw(buf);
	printf("%x\n", file_header.addr_size);
	printf("%x\n", file_header.endianness);
	printf("%x\n", file_header.abi);
	printf("%x\n", file_header.obj_type);

	printf("%s\n", XParse::ELF::to_string_raw(file_header).c_str());

	return 0;
}