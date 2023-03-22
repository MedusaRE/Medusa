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
#include <rome/rome.hpp>
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
		int ret;
		ret = wgetch(win);

		/*
		 *  TODO: document wtf is going on here
		 */
		if (ret == 27) {
			nodelay(win, true);
			ret = wgetch(win);
			nodelay(win, false);

			return (ret == -1) ? KEY_ESC : ret;
		} else {
			return ret;
		}
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

	void window::attron(int attr) {
		attron(attr);
	}

	void window::attroff(int attr) {
		attroff(attr);
	}

	void window::chgattr(int attr, int x, int y, int n, int color_pair) {
		int curx, cury;
		getyx(win, cury, curx);

		if (n < 0) {
			int cols, rows;
			getmaxyx(stdscr, cols, rows);

			n = (rows + (n));
		}

		mvwchgat(win, y, x, n, attr, color_pair, NULL);
		wmove(win, cury, curx);
	}

	void window::move(int x, int y) {
		wmove(win, y, x);
	}

	cur_pos_t window::get_cursor_pos() {
		cur_pos_t ret;

		getyx(win, ret.y, ret.x);

		return ret;
	}

	window::~window() {
		endwin();
	}
} //  namespace rome
