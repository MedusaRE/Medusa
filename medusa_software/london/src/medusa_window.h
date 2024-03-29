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

#ifndef MEDUSA_WINDOW_H
#define MEDUSA_WINDOW_H

#include "london.h"

#include <gtkmm.h>
#include <gtkmm/box.h>
#include <gtksourceviewmm.h>

class medusa_window: public Gtk::Window {
	public:
		medusa_window(int argc, char *argv[], Glib::RefPtr<Gtk::Application>);
		void on_startup();
		virtual ~medusa_window();

	protected:
		void on_action_file_new();
		void on_action_file_open();
		void on_action_file_open_folder();
		void on_action_file_save();
		void on_action_file_quit();
		void on_action_edit_copy();
		void on_action_edit_paste();

		void on_treeview_row_activated(const Gtk::TreeModel::Path& path,
									   Gtk::TreeViewColumn *);

		void open_file(std::string fn);

		void repopulate_directory_tree(Gtk::TreeModel::Row *parent = NULL,
									   std::string			path   = "");
		london_config_t lct;

		Glib::RefPtr<Gtk::TreeStore> ref_tree_model;
		Gtk::TreeView				 trv;

		class dir_view_column: public Gtk::TreeModel::ColumnRecord {
			public:
				dir_view_column() {
					add(dir_name);
					add(full_path);
				}

				Gtk::TreeModelColumn<Glib::ustring> dir_name;
				Gtk::TreeModelColumn<Glib::ustring> full_path;
		};

		Glib::RefPtr<Gsv::LanguageManager> lm;
		Gsv::View						  *tv;

		Glib::RefPtr<Gtk::Application> app;

		dir_view_column dir_view_columns;
};

#endif
