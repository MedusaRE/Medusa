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

#include "lib.h"

#include <iostream>
#include <ranges>
#include <stdio.h>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
	vector<string> split_s;
	string		   s;

	while (s != "exit") {
		getline(cin, s);

		split_s = str_split(s, ' ');

		printf("%s:\n", split_s.at(0).c_str());
		split_s.erase(split_s.begin());
		for (string arg: split_s) {
			printf("\t%s\n", arg.c_str());
		}
	}

	return 0;
}