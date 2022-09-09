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

#ifndef __ROME_ROME_HPP
#define __ROME_ROME_HPP

#include <ncurses.h>
#include <string>

#undef getch
#undef addstr
#undef attron
#undef attroff

namespace rome {
	static int KEY_ESC = 0x80000000;

	typedef struct {
		int x;
		int y;
	} cur_pos_t;

	class window {
		public:
			window();
			~window();

			int getch();
			void putch(int ch);
			void putch(int ch,
					   int x,
					   int y);

			void addstr(std::string str);
			void addstr(std::string str,
						int x,
						int y);

			void attron(int attr);
			void attroff(int attr);

			void chgattr(int arr,
						 int x,
						 int y,
						 int n,
						 int color_pair);

			void move(int x,
					  int y);
			cur_pos_t get_cursor_pos();

		private:
			WINDOW *win;
	};
}

#endif
