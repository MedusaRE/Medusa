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

#ifndef MEDUSA_MUNICH_HPP
#define MEDUSA_MUNICH_HPP

#include "../../src/lib.h"
#include <iostream>
#include <string>

namespace munich {
	class string : public std::string {
		public:
			template<typename... arg_type>
			string(const char* s, arg_type... args) {
				this->assign(string_format_cstr(s, args...));
			}

			operator const char*() {
				return this->c_str();
			}

			operator char*() const {
				return (char*)this->c_str();
			}
	};

    template<typename... arg_type>
	int printf(arg_type... args) {
		int i = 0;
		int n;

		([&] {
			std::cout << i << ": " << typeid(args).name() << ": " << args << std::endl;
			i++;
		} (), ...);

		return n;
	}
}

#endif
