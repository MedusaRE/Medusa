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
	Gtk::Window::set_default_icon_from_file("../../res/img/icon.png");

	medusa_log(LOG_INFO, "Landed in medusa_window.");

	set_default_size(800,
					 600);

	/*
	 *  create a TextView for the disassembly, as well as a TextBuffer for
	 *  containing the text
	 */
	medusa_log(LOG_VERBOSE, "Creating GTK TextView and TextBuffer...");
	auto* our_text_view   = new Gtk::TextView();
	auto  our_text_buffer = Gtk::TextBuffer::create();

	/*
	 *  monospace looks better :P
	 *  also we don't want it to be editable
	 */
	medusa_log(LOG_VERBOSE, "Setting TextView properties...");
	our_text_view->set_monospace(true);
	our_text_view->set_editable(false);
	our_text_view->set_buffer(our_text_buffer);

	/*
	 *  set the actual thing
	 */
	our_text_buffer->set_text("Example text.");

	/*
	 *  add text view to scrolledwindow and init scrolledwindow
	 */
	medusa_log(LOG_VERBOSE, "Initializing ScrolledWindow.");

	sw.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_ALWAYS);
	sw.set_propagate_natural_width(true);

	medusa_log(LOG_VERBOSE, "Adding TextView.");
	sw.add(*our_text_view);
	sw.show_all_children();

	medusa_log(LOG_VERBOSE, "Initializing step button.");
	step_button.set_label("step instruction");

	medusa_log(LOG_VERBOSE, "Initializing Register View.");
	reg_view.set_editable(false);
	reg_view.set_monospace(true);

	medusa_log(LOG_VERBOSE, "Attaching step button.");
	our_grid.attach(step_button, 0, 0);

	medusa_log(LOG_VERBOSE, "Initializing grid.");
	our_grid.set_column_homogeneous(false);
	our_grid.set_row_homogeneous(false);
	our_grid.set_margin_right(0);
	our_grid.set_margin_start(0);

	medusa_log(LOG_VERBOSE, "Packing button grid into button box.");
	button_box.pack_start(our_grid);

	medusa_log(LOG_VERBOSE, "Packing ScrolledWindow & Register View into emulation box.");
	emu_box.pack_start(sw);
	emu_box.pack_start(reg_view);

	medusa_log(LOG_VERBOSE, "Initializing button box.");
	button_box.set_spacing(10);
	button_box.set_center_widget(our_grid);

	medusa_log(LOG_VERBOSE, "Initializing emulation box.");
	emu_box.set_spacing(10);
	emu_box.set_homogeneous(true);

	medusa_log(LOG_VERBOSE, "Packing button box and emulation box into main box.");
	our_box.pack_start(button_box);
	our_box.pack_start(emu_box);

	medusa_log(LOG_VERBOSE, "Initializing main box.");
	our_box.set_homogeneous(false);
	our_box.set_border_width(10);

	medusa_log(LOG_VERBOSE, "Adding ScrolledWindow...");
	add(our_box);

	medusa_log(LOG_VERBOSE, "Showing...");
	show_all_children();
}

medusa_window::~medusa_window() {
	return;
}
