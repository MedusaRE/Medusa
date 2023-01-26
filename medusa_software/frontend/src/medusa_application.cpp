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

#include "medusa_application.h"

#include "medusa_window.h"

#include <gtkmm.h>

medusa_application::medusa_application() {
	//
}

Glib::RefPtr<medusa_application> medusa_application::create() {
	return Glib::RefPtr<medusa_application>(new medusa_application());
}

medusa_window *medusa_application::create_appwindow() {
	auto appwindow = new medusa_window();

	add_window(*appwindow);

	return appwindow;
}

void medusa_application::on_activate() {
	auto appwindow = create_appwindow();
	appwindow->present();
}