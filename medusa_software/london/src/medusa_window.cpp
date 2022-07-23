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

Glib::RefPtr<Gtk::TextBuffer> tvb;
bool bold_me = true;

void on_changed() {
	Gtk::TextIter begin, end;
	
	tvb->get_bounds(begin, end);

	if (bold_me) {
		tvb->remove_tag_by_name("red", begin, end);
		tvb->apply_tag_by_name("bold", begin, end);
		printf("bold\n");
	} else {
		tvb->remove_tag_by_name("bold", begin, end);
		tvb->apply_tag_by_name("red", begin, end);
		printf("red\n");
	}

	bold_me = !bold_me;
}

medusa_window::medusa_window(int   argc,
						   char* argv[]) {
	medusa_log(LOG_INFO, "Landed in medusa_window.");
	medusa_log(LOG_VERBOSE, "Showing...");

	auto* tv = new Gtk::TextView;
	tvb = Gtk::TextBuffer::create();

	tvb->create_tag("bold")->property_weight() = Pango::WEIGHT_BOLD;
	tvb->create_tag("red")->property_foreground() = "#ff0000";
	auto normal_tag = tvb->create_tag("normal");
	normal_tag->property_weight() = Pango::WEIGHT_NORMAL;
	normal_tag->property_foreground() = "#ffffff";

	tvb->set_text("yahtzee");
	tvb->apply_tag_by_name("bold", tvb->get_iter_at_line_offset(0, 0), tvb->get_iter_at_line_offset(0, 4));
	tvb->apply_tag_by_name("bold", tvb->get_iter_at_line_offset(0, 2), tvb->get_iter_at_line_offset(0, 6));
	tvb->apply_tag_by_name("red", tvb->get_iter_at_line_offset(0, 2), tvb->get_iter_at_line_offset(0, 6));
	tvb->apply_tag_by_name("red", tvb->get_iter_at_line_offset(0, 4), tvb->get_iter_at_line_offset(0, 8));

	tvb->signal_changed().connect(sigc::ptr_fun(&on_changed));

	tv->set_buffer(tvb);

	auto* grid = new Gtk::Grid;

	grid->attach(*tv, 0, 0);
	grid->show_all();

	add(*grid);
	set_title("noround");

	show_all_children();
}

medusa_window::~medusa_window() {
	//
}
