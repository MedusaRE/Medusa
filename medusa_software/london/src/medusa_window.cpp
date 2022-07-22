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

#include <capstone/capstone.h>
#include <unicorn/unicorn.h>
#include "medusa_window.h"
#include "logging.h"
#include <gtkmm.h>
#include "lib.h"

using namespace std;

medusa_window::medusa_window(int   argc,
						   char* argv[]) {
	medusa_log(LOG_INFO, "Landed in medusa_window.");
	medusa_log(LOG_VERBOSE, "Showing...");

	auto* tv = new Gtk::TextView;
	auto tvb = Gtk::TextBuffer::create();

	tvb->set_text("yahtzee");
	tv->set_buffer(tvb);

	add(*tv);
	set_title("noround");

	show_all_children();
}

medusa_window::~medusa_window() {
	//
}
