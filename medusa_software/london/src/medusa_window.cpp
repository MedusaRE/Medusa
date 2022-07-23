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
#include <fstream>
#include <gtkmm.h>
#include "lib.h"
#include <iostream>

using namespace std;

bool						   bold_me = true;
char						  *filename;
Glib::RefPtr<Gtk::TextBuffer>  tvb;

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
//		tvb->apply_tag_by_name("bold", begin, end);

		#if DEBUG_BUILD
			printf("bold\n");
		#endif
	} else {
		tvb->remove_tag_by_name("bold", begin, end);
//		tvb->apply_tag_by_name("red", begin, end);
		
		#if DEBUG_BUILD
			printf("red\n");
		#endif
	}

	bold_me = !bold_me;
}

void medusa_window::on_open_clicked() {
	Gtk::FileChooserDialog dialog("Please choose a file to edit.",
								  Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialog.set_transient_for(*this);

	dialog.add_button("_Cancel",	Gtk::RESPONSE_CANCEL);
	dialog.add_button("_Open",		Gtk::RESPONSE_OK);

	int result = dialog.run();
	switch (result) {
		case (Gtk::RESPONSE_OK): {
			/*
			 *  strdup because otherwise it breaks or something
			 *  god, i love memory management
			 */

			medusa_log(LOG_INFO, "User chose to open file.");
			filename = strdup(dialog.get_filename().c_str());
			medusa_log(LOG_INFO, "Filename: %s", filename);
			break;
		} case (Gtk::RESPONSE_CANCEL): {
			medusa_log(LOG_INFO, "User cancelled file opening.");
			filename = NULL;
			break;
		} default: {
			medusa_log(LOG_ERROR, "Something went wrong.");
			return;
			break;
		}
	}

	ifstream	 f(filename);
	stringstream ss;
	
	ss << f.rdbuf();
	tvb->set_text(ss.str());

	f.close();
}

void medusa_window::on_save_clicked() {
	string		 txt_str = tvb->get_text();
	const char	*txt	 = txt_str.c_str();
	ofstream	 f(filename);

	f.write(strdup(txt), strlen(txt));

	f.close();
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

//	tvb->set_text("yahtzee");
	tvb->apply_tag_by_name("bold", tvb->get_iter_at_line_offset(0, 0), tvb->get_iter_at_line_offset(0, 4));
	tvb->apply_tag_by_name("bold", tvb->get_iter_at_line_offset(0, 2), tvb->get_iter_at_line_offset(0, 6));
	tvb->apply_tag_by_name("red", tvb->get_iter_at_line_offset(0, 2), tvb->get_iter_at_line_offset(0, 6));
	tvb->apply_tag_by_name("red", tvb->get_iter_at_line_offset(0, 4), tvb->get_iter_at_line_offset(0, 8));

	tvb->signal_insert().connect(sigc::ptr_fun(&on_insert));

	tv->set_buffer(tvb);

	auto* grid = new Gtk::Grid;
	auto* open_btn = new Gtk::Button;
	auto* save_btn = new Gtk::Button;

	open_btn->set_label("open");
	open_btn->signal_clicked().connect(sigc::mem_fun(*this, &medusa_window::on_open_clicked));

	save_btn->set_label("save");
	save_btn->signal_clicked().connect(sigc::mem_fun(*this, &medusa_window::on_save_clicked));

	grid->attach(*tv, 0, 1);
	grid->attach(*open_btn, 0, 0);
	grid->attach(*save_btn, 1, 0);
	
	grid->set_row_homogeneous(false);
	grid->set_column_homogeneous(false);
	grid->set_hexpand(false);
	grid->set_vexpand(false);

	grid->show_all();

	add(*grid);

	/*
	 *  noround is part of my (spv) personal setup.
	 *  i use rounded corners, and in my picom.conf i have it set so that if a
	 *  window title contains "noround", it will not have rounded corners.
	 *
	 *  i have this set right now because otherwise it will cut off part of the
	 *  actual content, as there isn't a toolbar or anything.
	 */
	set_title("London (noround)");

	show_all_children();
}

medusa_window::~medusa_window() {
	//
}
