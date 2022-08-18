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

namespace rome {
	static int KEY_ESC = 0x80000000;

	class window {
		public:
			window();
			~window();

			int getch();
			void putch(int ch);
			void putch(int ch, int x, int y);

			void addstr(std::string str);
			void addstr(std::string str, int x, int y);

		private:
			WINDOW *win;
	};
}

#endif
