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

void on_insert(const Gtk::TextIter& pos,
			   const Glib::ustring& text,
			   const int& bytes) {
	Gtk::TextIter begin, end;
	
	begin = pos;
	end = pos;

	#if DEBUG_BUILD
		printf("%d %d %d\n", bytes, begin.get_offset(), end.get_offset());
	#endif

	begin.set_offset(begin.get_offset() - 1);
	end.set_offset(end.get_offset() + bytes - 1);

	#if DEBUG_BUILD
		printf("%d %d %d\n", bytes, begin.get_offset(), end.get_offset());
	#endif

	if (bold_me) {
		tvb->remove_tag_by_name("red", begin, end);
		tvb->apply_tag_by_name("bold", begin, end);

		#if DEBUG_BUILD
			printf("bold\n");
		#endif
	} else {
		tvb->remove_tag_by_name("bold", begin, end);
		tvb->apply_tag_by_name("red", begin, end);
		
		#if DEBUG_BUILD
			printf("red\n");
		#endif
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

	tvb->signal_insert().connect(sigc::ptr_fun(&on_insert));

	tv->set_buffer(tvb);

	auto* grid = new Gtk::Grid;
	auto* btn = new Gtk::Button;

	btn->set_label("yahtzee");

	grid->attach(*tv, 0, 1);
	grid->attach(*btn, 0, 0);
	grid->show_all();
	grid->set_row_homogeneous(false);
	grid->set_column_homogeneous(false);
	grid->set_hexpand(false);
	grid->set_vexpand(false);

	add(*grid);
	set_title("noround");

	show_all_children();
}

medusa_window::~medusa_window() {
	//
}
