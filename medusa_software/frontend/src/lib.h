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

#ifndef LIB_H
#define LIB_H

#include <sys/resource.h>
#include <stdarg.h>
#include <memory>
#include <string>
#include <vector>

#ifndef LIB_H_NO_BUILD_GUI

#include <gtkmm.h>

std::string file_prompt(enum Gtk::FileChooserAction action, std::string title);
char* file_prompt_cstr(enum Gtk::FileChooserAction action, std::string title);

#endif

std::string string_format_cstr(const char* fmt_str, ...);
std::string string_format(const std::string fmt_str, ...);
std::string getcwd_str();

#define LIST_LEN(l) (sizeof(l) / sizeof(l[0]))

#define U8X2_TO_U16(u0, u1)			((u0 << 8) | (u1 << 0))
#define U8X4_TO_U32(u0, u1, u2, u3)	((U8X2_TO_U16(u0, u1) << 16) \
									 | (U8X2_TO_U16(u2, u3) << 0))
#define U8X8_TO_U64(u0, u1, u2, u3, \
					u4, u5, u6, u7)	(((uint64_t)U8X4_TO_U32(u0, u1, u2, u3) << 32) \
									 | ((uint64_t)U8X4_TO_U32(u4, u5, u6, u7) << 0))

std::vector<std::string> str_split(std::string s, std::string delim);

uint64_t get_statm_usage(void);

#define DEBUG_INFO() do { \
	fprintf(stderr, "%s (%d): mem_usage=%ldKB\n", __FILE__, __LINE__, get_statm_usage()); \
} while(0)

#endif
