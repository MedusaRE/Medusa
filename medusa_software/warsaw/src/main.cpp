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

#include <warsaw/ARMv7Machine.hpp>
#include <warsaw/Machine.hpp>
#include <paris/message.hpp>
#include <paris/paris.hpp>
#include <unistd.h>
#include <cstdio>

int main(int argc, char* argv[]) {
	paris::Server server;

	warsaw::ARMv7Machine armv7_machine_service;

	server.start_server();

	server.add_service(armv7_machine_service);

	paris::paris_message_t msg;

	msg.service_id = armv7_machine_service.get_service_id();
	msg.uid = 420;

	server.send_message(msg);

	sleep(1);
	server.stop_server();

	return 0;
}