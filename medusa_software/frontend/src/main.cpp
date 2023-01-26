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

#include "logging.h"
#include "medusa_application.h"
#include "medusa_window.h"

#include <cstdio>
#include <gtkmm.h>
#include <paris/message.hpp>
#include <paris/paris.hpp>

int main(int argc, char *argv[]) {
	medusa_set_log_level(LOG_VERBOSE);
	medusa_log(LOG_INFO, "Medusa loaded.");

	/*
	 *	TODO: use something that isn't deprecated!
	 *
	 *	gdk_threads_init(void); is deprecated.
	 */
	gdk_threads_init();

	auto application = medusa_application::create();
	medusa_log(LOG_INFO, "Created medusa_application object.");

	medusa_log(LOG_INFO, "application->run(...);");
	return application->run(argc, argv);
}
