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
#include <jpcre2.hpp>

using namespace std;
typedef jpcre2::select<char> jp;

int main(int argc, char *argv[]) {
	printf("Hello, world!\n");
	jp::Regex re;
	re.setPattern("ldr (r[0-9]+|sp|ip|lr|pc|fp), \\[(r[0-9]+|sp|ip|lr|pc|fp), (r[0-9]+|sp|ip|lr|pc|fp), lsl #2\\]");
	std::string s = jp::Regex("ldr (r[0-9]+|sp|ip|lr|pc|fp), \\[(r[0-9]+|sp|ip|lr|pc|fp), (r[0-9]+|sp|ip|lr|pc|fp), lsl #2\\]")
						.initReplace()
						.setSubject("ABC! ldr r0, [r0, r1, lsl #2] DEF!")
						.setReplaceWith("$1 = $2[$3];")
						.replace();

	printf("%s\n", s.c_str());

	return 0;
}