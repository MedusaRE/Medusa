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

#include "london.h"

#include "config.h"
#include "lib.h"

london_config_t parse_config_file(const char *filename) {
	if (filename == NULL) {
		filename = strcat(getenv("HOME"), "/.medusa/london.ini");
	}

	mINI::INIFile	   file(filename);
	mINI::INIStructure ini;

	london_config_t ret;

	file.read(ini);
	ret.tab_size	 = stoi(ini["global"]["tab-size"]);
	ret.hard_tabs	 = ini["global"]["hard-tabs"] == "true";
	ret.default_path = ini["global"]["default-path"];

#if DEBUG_BUILD
	printf("%d %s %s\n", ret.tab_size, ret.hard_tabs ? "true" : "false", ret.default_path);
#endif

	return ret;
}