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

#include <cstdio>
#include <medusa/munich.hpp>

#if 0
using namespace munich;

template<typename... arg_type>
string::string(const char* s, arg_type... args) {
	this->assign(string_format_cstr(s, args...));
}

string::operator const char *() const {
	return this->c_str();
}

template string::string(const char *, int);
#endif