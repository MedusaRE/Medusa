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

#include <getopt.h>
#include <cstdio>

int main(int argc, char* argv[]) {
	int c;

	struct option long_options[] = {
		{"example_option_1", required_argument, 0, 0},
		{"example_option_2", optional_argument, 0, 'o'},
		{0, 0, 0, 0},
	};

	while (true) {
		int option_index = 0;
		c = getopt_long(argc, argv, "o:", long_options, &option_index);

		if (c == -1) {
			break;
		}

		switch (c) {
			case 0:
				printf("option %s=%s\n", long_options[option_index].name, optarg);
				break;
			case 'o':
				printf("option %c=%s\n", c, optarg);
				break;
			default:
				;
		}

	}

	if (optind < argc) {
		while (optind < argc) {
			printf("%s ", argv[optind++]);
		}

		printf("\n");
	}

	return 0;
}