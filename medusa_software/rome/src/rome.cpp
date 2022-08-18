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
#include <string>

namespace rome {
	window::window() {
		initscr();
		cbreak();
		noecho();

		keypad(stdscr, TRUE);

		int cols, rows;
		getmaxyx(stdscr, cols, rows);

		win = newwin(cols, rows, 0, 0);
	}

	int window::getch() {
		return wgetch(win);
	}

	void window::putch(int ch) {
		waddch(win, ch);
	}

	void window::putch(int ch, int x, int y) {
		int curx, cury;
		getyx(win, cury, curx);

		mvwaddch(win, y, x, ch);
		wmove(win, cury, curx);
	}

	void window::addstr(std::string str) {
		waddstr(win, str.c_str());
	}

	void window::addstr(std::string str, int x, int y) {
		int curx, cury;
		getyx(win, cury, curx);

		mvwaddstr(win, y, x, str.c_str());
		wmove(win, cury, curx);
	}

	window::~window() {
		endwin();

		printf("rip\n");
	}
}
