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
#include <ncurses.h>

#define KEY_ESC 27

int main(int argc, char *argv[]) {
	initscr();
	cbreak();
	noecho();

	keypad(stdscr, TRUE);

	int cols, rows;
	getmaxyx(stdscr, cols, rows);

	WINDOW *win = newwin(cols, rows, 0, 0);

	wmove(win, 1, 3);

	waddstr(win, "barcelona");
	wmove(win, 1, (rows - strlen("Hello, world!")) / 2);
	waddstr(win, "Hello, world!");

	wmove(win, 1, (rows - strlen("Second String") - 3));
	waddstr(win, "Second String");

	mvwchgat(win, 1, 1, rows - 2, A_REVERSE, 0, NULL);

	wmove(win, 3, 1);

	while (1) {
		int ch;
		ch = wgetch(win);

		if (ch == KEY_ESC) {
			goto out;
		}

		waddch(win, ch);
	}

out:
	endwin();

	return 0;
}
