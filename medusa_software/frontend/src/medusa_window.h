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

#ifndef MEDUSA_WINDOW_H
#define MEDUSA_WINDOW_H

#include <paris/paris.hpp>
#include <gtkmm.h>

class TextTestService : public paris::ServiceListener {
	public:
		virtual bool process_message(paris::paris_message_t message, paris::Server* server);
		Glib::RefPtr<Gtk::TextBuffer> our_text_buffer;
};

class medusa_window : public Gtk::Window {
	public:
		medusa_window();
		virtual ~medusa_window();
		TextTestService service;
		paris::Server server;
	protected:
		Gtk::Button step_button;
		Gtk::ScrolledWindow sw;
		Gtk::TextView reg_view;
		Gtk::Box button_box;
		Gtk::Grid our_grid;
		Gtk::Box emu_box;
		Gtk::Box our_box;
};

#endif
