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

#include <rome.hpp>
#include <cstdio>

int main(int   argc,
		 char *argv[]) {
	rome::window window;

	window.addstr("rome test", 3, 1);
	window.chgattr(A_REVERSE, 1, 1, -2, 0);

	int esc_count = 0;

	window.move(1, 3);

	while (true) {
		int ch;
		ch = window.getch();

		window.putch(ch);

		if (ch == rome::KEY_ESC && (esc_count == 0)) {
			window.addstr("Are you sure you would like to exit? Press ESCAPE"
						  " again if so.", 0, 0);
			esc_count++;
		} else if (ch == rome::KEY_ESC && (esc_count == 1)) {
			return 0;
		} else {
			esc_count = 0;
		}
	}

	return 0;
}
