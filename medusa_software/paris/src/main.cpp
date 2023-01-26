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

#include "lib.h"

#include <cstdio>
#include <iostream>
#include <paris/message.hpp>
#include <paris/paris.hpp>
#include <stddef.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <thread>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {
	DEBUG_PRINTF("creating Server object\n");

	cin.get();

	paris::Server server;

	DEBUG_PRINTF("starting server\n");
	server.start_server();

	cin.get();

	DEBUG_PRINTF("creating Service's\n");
	paris::ExampleService service1;
	paris::ExampleService service2;

	paris::DumpMsgContentsToSTDOUTService stdout_service;

	cin.get();

	DEBUG_PRINTF("adding Service's\n");
	server.add_service(service1);
	server.add_service(service2);
	server.add_service(stdout_service);

	cin.get();

	uint64_t tmp = 0x4142434445464748;

	paris::paris_message_t message;
	message.service_id	 = stdout_service.get_service_id();
	message.len			 = 8;
	message.msg_contents = (uint8_t *)&tmp;

	DEBUG_PRINTF("sending stdout test\n");
	server.send_message(message);

	cin.get();

	message.service_id	 = PARIS_SERVER_SERVICE_ID;
	message.message_type = paris::REGISTER_SESSION;
	message.service_by	 = stdout_service.get_service_id();

	DEBUG_PRINTF("sending REGISTER_SESSION\n");
	server.send_message(message);
	cin.get();

	DEBUG_PRINTF("sending message to service1 (%lx)\n", service1.get_service_id());
	message.uid		   = 42;
	message.service_id = service1.get_service_id();
	server.send_message(message);

	cin.get();
	DEBUG_PRINTF("sending message to service2 (%lx)\n", service2.get_service_id());
	message.uid		   = 43;
	message.service_id = service2.get_service_id();
	server.send_message(message);

	cin.get();

	DEBUG_PRINTF("stopping server\n");
	server.stop_server();
	sleep(1);

	return 0;
}
