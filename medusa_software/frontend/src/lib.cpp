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

#ifndef LIB_H_NO_BUILD_GUI
#include "logging.h"
#include <gtkmm.h>
#endif

#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <sstream>
#include <memory>
#include <random>
#include <string>
#include <vector>

using namespace std;

string string_format(const string fmt_str, ...) {
	/*
	 *  reserve two times as much as the length of the fmt_str
	 */
	int final_n, n = ((int)fmt_str.size()) * 2;

	unique_ptr<char[]> formatted;
	va_list ap;

	while (1) {
		/*
		 *  wrap the plain char array into the unique_ptr
		 */
		formatted.reset(new char[n]);

		strcpy(&formatted[0], fmt_str.c_str());

		va_start(ap, fmt_str);
		final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
		va_end(ap);

		if (final_n < 0 || final_n >= n) {
			n += abs(final_n - n + 1);
		} else {
			break;
		}
	}

	return string(formatted.get());
}

string string_format_cstr(const char* fmt_str, ...) {
	/*
	 *  reserve two times as much as the length of the fmt_str
	 */
	int final_n, n = ((int)strlen(fmt_str)) * 2;

	unique_ptr<char[]> formatted;
	va_list ap;

	while (1) {
		/*
		 *  wrap the plain char array into the unique_ptr
		 */
		formatted.reset(new char[n]);

		strcpy(&formatted[0], fmt_str);

		va_start(ap, fmt_str);
		final_n = vsnprintf(&formatted[0], n, fmt_str, ap);
		va_end(ap);

		if (final_n < 0 || final_n >= n) {
			n += abs(final_n - n + 1);
		} else {
			break;
		}
	}

	return string(formatted.get());
}

#ifndef LIB_H_NO_BUILD_GUI

std::string file_prompt(enum Gtk::FileChooserAction action, std::string title) {
	Gtk::FileChooserDialog dialog(title,
									  action);
	std::string			   ret;

	dialog.add_button("_Cancel",	Gtk::RESPONSE_CANCEL);
	dialog.add_button("_Open",		Gtk::RESPONSE_OK);

	int result = dialog.run();
	switch (result) {
		case (Gtk::RESPONSE_OK): {
			ret = dialog.get_filename();
			medusa_log(LOG_VERBOSE, "User chose to open %s.", ret.c_str());
			break;
		} case (Gtk::RESPONSE_CANCEL): {
			medusa_log(LOG_VERBOSE, "User cancelled file opening.");
			ret = "";
			break;
		} default: {
			medusa_log(LOG_ERROR, "Something went wrong.");
			ret = "";
			break;
		}
	}
	return ret;
}

char* file_prompt_cstr(enum Gtk::FileChooserAction action, std::string title) {
	std::string ret_str = file_prompt(action, title);
	return ret_str == "" ? NULL : strdup(ret_str.c_str());
}

#endif

std::string getcwd_str() {
	char cwd[1024];
	getcwd(cwd, 1024);

	return std::string(cwd);
}

std::vector<std::string> str_split(std::string& s, char delim) {
	std::vector<std::string> ret;
	std::stringstream ss(s);

	std::string token;
	size_t pos = 0;

	while (std::getline(ss, token, delim)) {
		ret.push_back(token);
	}

	return ret;
}

uint64_t get_statm_usage(void) {
	FILE* fp = fopen("/proc/self/statm", "r");
	uint64_t ret;

	fscanf(fp, "%ld", &ret);
	fclose(fp);

	return ret;
}

uint64_t medusa_rand(void) {
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<uint64_t> dis;

	return dis(gen);
}