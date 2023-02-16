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
#include "medusa_window.h"

#include <cstdio>
#include <filesystem>
#include <gtkmm.h>

using namespace std;

int main(int argc, char *argv[]) {
	/*
	 *  TODO: make this code look better, it looks like shit.
	 *
	 *  This code creates a fake argc and argv that only contains the name of
	 *  the binary, otherwise GTK gets mad at the moment, complaining that we
	 *  don't take files as arguments or something.
	 *
	 *  spv@jkek420:/.../xpdbg/xpdbg_software$ bin/main res/test1.bin
	 *
	 *  (main:13170): GLib-GIO-CRITICAL **: 14:22:18.291: This application can
	 * not open files. spv@jkek420:/.../xpdbg/xpdbg_software$
	 */
	int	   fake_argc = 1;
	char **fake_argv = NULL;
	fake_argv		 = (char **)calloc(sizeof(uintptr_t), 2);

	//	ls_dir("/home/spv/test", 0);
	//	return 0;

	/*
	 *  populate the array
	 */
	fake_argv[0] = argv[0];
	fake_argv[1] = NULL;

	medusa_set_log_level(LOG_VERBOSE);
	medusa_log(LOG_INFO, "Medusa loaded.");

	/*
	 *  create the app
	 */
	medusa_log(LOG_INFO, "Creating GTK application...");
	auto app = Gtk::Application::create(fake_argc, fake_argv, "org.medusa-re.medusa");

	/*
	 *  create the window object
	 */
	medusa_log(LOG_INFO, "Creating medusa_window...");
	medusa_window window(argc, argv);
	app->signal_startup().connect(sigc::mem_fun(window, &medusa_window::on_startup));

	/*
	 *  run it
	 */
	medusa_log(LOG_INFO, "Running medusa_window...");
	return app->run(window);
}
