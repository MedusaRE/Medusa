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

#include "medusa_window.h"

#include "../../submodules/mINI/src/mini/ini.h"
#include "config.h"
#include "lib.h"
#include "logging.h"
#include "london.h"

#include <capstone/capstone.h>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <gtkmm.h>
#include <gtkmm/application.h>
#include <gtkmm/box.h>
#include <gtkmm/menu.h>
#include <gtkmm/menubar.h>
#include <gtkmm/menuitem.h>
#include <gtkmm/toolbutton.h>
#include <gtksourceviewmm.h>
#include <iostream>
#include <unicorn/unicorn.h>

using namespace std;
namespace fs = std::filesystem;

bool						  bold_me = true;
char						 *filename;
Glib::RefPtr<Gtk::TextBuffer> tvb;

void on_insert(const Gtk::TextIter& pos, const Glib::ustring& text, const int& bytes) {
	/*
	 *  this signal is currently unused.
	 */
}

void on_changed() {
	Gtk::TextIter begin, end;

	/*
	 *  ensure monospace
	 */
	tvb->get_bounds(begin, end);
	tvb->apply_tag_by_name("monospace_default", begin, end);
}

void medusa_window::open_file(std::string filename) {
	ifstream	 f(filename);
	stringstream ss;

	ss << f.rdbuf();

	tvb = Gsv::Buffer::create(lm->guess_language(filename, ""));
	tv->set_buffer(tvb);
	tvb = tv->get_buffer();

	auto monospace_tag			   = tvb->create_tag("monospace_default");
	monospace_tag->property_font() = "Inconsolata 10";

	tvb->set_text(ss.str());

	f.close();
}

void medusa_window::on_action_file_open() {
	filename = file_prompt_cstr(Gtk::FILE_CHOOSER_ACTION_OPEN, "Please choose a file to edit.");
	if (filename == NULL) {
		return;
	}

	open_file(filename);
}

void medusa_window::on_open_folder_clicked() {
	char *folder_name = file_prompt_cstr(Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER,
										 "Please choose a folder to open.");
	if (folder_name == NULL) {
		return;
	}

	std::string folder = folder_name;
	chdir(folder.c_str());

	this->repopulate_directory_tree();
}

void medusa_window::on_save_clicked() {
	while (filename == NULL) {
		filename = file_prompt_cstr(Gtk::FILE_CHOOSER_ACTION_SAVE,
									"Please create a file to save to.");
	}

	string		txt_str = tvb->get_text();
	const char *txt		= txt_str.c_str();
	ofstream	f(filename);

	f.write(strdup(txt), strlen(txt));

	f.close();
}

void medusa_window::repopulate_directory_tree(Gtk::TreeModel::Row *parent, std::string path) {
	/*
	 *  path defaults to "", so i fit is unspecified, it will create a new
	 *  (blank / empty) TreeStore.
	 */
	if (path == "") {
		ref_tree_model = Gtk::TreeStore::create(dir_view_columns);
		trv.set_model(ref_tree_model);
		path = getcwd_str();
	}

	for (const fs::directory_entry& entry: fs::directory_iterator(path)) {
		Gtk::TreeModel::Row row;

		if (!parent) {
			row = *(ref_tree_model->append());
		} else {
			row = *(ref_tree_model->append(parent->children()));
		}

		row[dir_view_columns.dir_name]	= entry.path().filename().string();
		row[dir_view_columns.full_path] = entry.path().string();

		if (entry.is_directory()) {
			this->repopulate_directory_tree(&row, entry.path());
		}
	}
}

void medusa_window::on_treeview_row_activated(const Gtk::TreeModel::Path& path,
											  Gtk::TreeViewColumn *) {
	Gtk::TreeModel::iterator iter = ref_tree_model->get_iter(path);
	if (iter) {
		Gtk::TreeModel::Row row = *iter;
		Glib::ustring		str = row.get_value(dir_view_columns.full_path);
		open_file(str);
	}
}

void medusa_window::on_startup() {}

medusa_window::medusa_window(int argc, char *argv[]) {
	medusa_log(LOG_INFO, "Landed in medusa_window.");
	medusa_log(LOG_VERBOSE, "Showing...");

	lct = parse_config_file(NULL);

	chdir(lct.default_path.c_str());

	Gsv::init();

	tv					 = manage(new Gsv::View);
	lm					 = Gsv::LanguageManager::create();
	vector<string> langs = lm->get_language_ids();

#if DEBUG_BUILD
	for (auto& i: langs) {
		printf("%s\n", i.c_str());
	}
#endif

	tvb = Gsv::Buffer::create();
	tv->set_buffer(tvb);
	tvb = tv->get_buffer();

	tv->set_tab_width(lct.tab_size);
	tv->set_insert_spaces_instead_of_tabs(!lct.hard_tabs);

	tv->set_monospace(true);

	tv->set_show_line_numbers(true);

	tvb->create_tag("bold")->property_weight()	  = Pango::WEIGHT_BOLD;
	tvb->create_tag("red")->property_foreground() = "#ff0000";

	auto normal_tag					  = tvb->create_tag("normal");
	normal_tag->property_weight()	  = Pango::WEIGHT_NORMAL;
	normal_tag->property_foreground() = "#ffffff";

	auto monospace_tag			   = tvb->create_tag("monospace_default");
	monospace_tag->property_font() = "Inconsolata 10";

	Gtk::TextIter begin, end;

	tvb->get_bounds(begin, end);
	tvb->apply_tag_by_name("monospace_default", begin, end);

	tvb->signal_insert().connect(sigc::ptr_fun(&on_insert));
	tvb->signal_changed().connect(sigc::ptr_fun(&on_changed));

	tv->set_buffer(tvb);

	auto *grid			  = new Gtk::Grid;
	auto *toolbar		  = new Gtk::Grid;
	auto *open_folder_btn = new Gtk::Button;
//	auto *open_btn		  = new Gtk::Button;
	auto *save_btn		  = new Gtk::Button;
	auto *sv			  = new Gtk::ScrolledWindow;
	auto *sv2			  = new Gtk::ScrolledWindow;
	auto *paned			  = new Gtk::Paned;

	ref_tree_model = Gtk::TreeStore::create(dir_view_columns);
	trv.set_model(ref_tree_model);

	this->repopulate_directory_tree();

	trv.append_column("Directory Browser", dir_view_columns.dir_name);
	trv.signal_row_activated().connect(sigc::mem_fun(*this, &medusa_window::on_treeview_row_activated));

//	open_btn->set_label("Open");
//	open_btn->signal_clicked().connect(sigc::mem_fun(*this, &medusa_window::on_open_clicked));

	open_folder_btn->set_label("Open Folder");
	open_folder_btn->signal_clicked().connect(sigc::mem_fun(*this, &medusa_window::on_open_folder_clicked));

	save_btn->set_label("Save");
	save_btn->signal_clicked().connect(sigc::mem_fun(*this, &medusa_window::on_save_clicked));

	sv->add(*tv);
	sv->set_hexpand(true);
	sv->set_vexpand(true);
	sv2->add(trv);

	paned->add1(*sv2);

//	toolbar->attach(*open_btn, 0, 0);
	toolbar->attach(*open_folder_btn, 1, 0);
	toolbar->attach(*save_btn, 2, 0);

	grid->set_row_homogeneous(false);
	grid->set_column_homogeneous(false);
	grid->set_hexpand(false);
	grid->set_vexpand(false);

	toolbar->set_row_homogeneous(false);
	toolbar->set_column_homogeneous(false);

	grid->show_all();

	paned->add2(*grid);

	paned->set_position(256);

	Gtk::Toolbar	*tb	  = new Gtk::Toolbar;
	Gtk::ToolButton *open = new Gtk::ToolButton(Gtk::Stock::OPEN);
	Gtk::ToolButton *dir  = new Gtk::ToolButton(Gtk::Stock::DIRECTORY);
	Gtk::ToolButton *save = new Gtk::ToolButton(Gtk::Stock::SAVE);

//	open->signal_clicked().connect(sigc::mem_fun(this, &medusa_window::on_open_clicked));
//	dir->signal_clicked().connect(sigc::mem_fun(this, &medusa_window::on_open_folder_clicked));
//	save->signal_clicked().connect(sigc::mem_fun(this, &medusa_window::on_save_clicked));

	tb->add(*open);
	tb->add(*dir);
	tb->add(*save);

	//	auto parent_box = new Gtk::Box;
	auto parent_grid = new Gtk::Grid;

	parent_grid->set_column_homogeneous(true);
	parent_grid->set_row_homogeneous(false);

	grid->set_hexpand();
	grid->set_vexpand();

	Glib::RefPtr<Gtk::Builder> m_refBuilder = Gtk::Builder::create();

	auto m_refActionGroup = Gio::SimpleActionGroup::create();

//	m_refActionGroup->add_action("new", sigc::mem_fun(*this, &medusa_window::on_action_file_new));
	m_refActionGroup->add_action("open", sigc::mem_fun(*this, &medusa_window::on_action_file_open));
//	m_refActionGroup->add_action("quit", sigc::mem_fun(*this, &medusa_window::on_action_file_quit));

	insert_action_group("medusa", m_refActionGroup);

	const char *ui_info = "<interface>"
						  "  <menu id='menubar'>"
						  "    <submenu>"
						  "      <attribute name='label' translatable='yes'>_File</attribute>"
						  "      <section>"
						  "        <item>"
						  "          <attribute name='label' translatable='yes'>_New</attribute>"
						  "          <attribute name='action'>medusa.new</attribute>"
						  "          <attribute name='accel'>&lt;Primary&gt;n</attribute>"
						  "        </item>"
						  "      </section>"
						  "      <section>"
						  "        <item>"
						  "          <attribute name='label' translatable='yes'>_Open</attribute>"
						  "          <attribute name='action'>medusa.open</attribute>"
						  "          <attribute name='accel'>&lt;Primary&gt;o</attribute>"
						  "        </item>"
						  "      </section>"
						  "      <section>"
						  "        <item>"
						  "          <attribute name='label' translatable='yes'>_Quit</attribute>"
						  "          <attribute name='action'>medusa.quit</attribute>"
						  "          <attribute name='accel'>&lt;Primary&gt;q</attribute>"
						  "        </item>"
						  "      </section>"
						  "    </submenu>"
						  "    <submenu>"
						  "      <attribute name='label' translatable='yes'>_Edit</attribute>"
						  "      <item>"
						  "        <attribute name='label' translatable='yes'>_Copy</attribute>"
						  "        <attribute name='action'>medusa.copy</attribute>"
						  "        <attribute name='accel'>&lt;Primary&gt;c</attribute>"
						  "      </item>"
						  "      <item>"
						  "        <attribute name='label' translatable='yes'>_Paste</attribute>"
						  "        <attribute name='action'>medusa.paste</attribute>"
						  "        <attribute name='accel'>&lt;Primary&gt;v</attribute>"
						  "      </item>"
						  "    </submenu>"
						  "  </menu>"
						  "</interface>";

	m_refBuilder->add_from_string(ui_info);

	Glib::RefPtr<Glib::Object> object = m_refBuilder->get_object("menubar");
	Glib::RefPtr<Gio::Menu> gmenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(object);
	Gtk::MenuBar *pMenuBar = Gtk::make_managed<Gtk::MenuBar>(gmenu);

	//	grid->attach(*pMenuBar, 0, 0);

	grid->attach(*sv, 0, 0);
	//	grid->attach(*toolbar, 0, 0);

	parent_grid->attach(*pMenuBar, 0, 0);
	parent_grid->attach(*paned, 0, 1);

	//	parent_box->pack_start(*tb);
	//	parent_box->pack_start(*paned);

	add(*parent_grid);

	/*
	 *  noround is part of my (spv) personal setup.
	 *  i use rounded corners, and in my picom.conf i have it set so that if a
	 *  window title contains "noround", it will not have rounded corners.
	 *
	 *  i have this set right now because otherwise it will cut off part of the
	 *  actual content, as there isn't a toolbar or anything.
	 */
	//	set_title("London (noround)");
	set_title("London");

	show_all_children();
}

medusa_window::~medusa_window() {
	//
}
