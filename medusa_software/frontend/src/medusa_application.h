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

#ifndef MEDUSA_APPLICATION_H
#define MEDUSA_APPLICATION_H

#include <gtkmm.h>

class medusa_window;

class medusa_application: public Gtk::Application {
	public:
		medusa_application();
		static Glib::RefPtr<medusa_application> create();

	protected:
		Gtk::Button			paris_test_button;
		Gtk::ScrolledWindow sw;
		Gtk::TextView		reg_view;
		Gtk::Box			button_box;
		Gtk::Grid			our_grid;
		Gtk::Box			emu_box;
		Gtk::Box			our_box;

		void step_clicked();
		void on_activate() override;

	private:
		medusa_window *create_appwindow();
};

#endif
