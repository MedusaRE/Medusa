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

#include <sys/socket.h>
#include "message.hpp"
#include "paris.hpp"
#include <stddef.h>
#include <stdlib.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstdio>
#include <thread>
#include "lib.h"

using namespace std;

int main(int argc, char* argv[]) {
	DEBUG_PRINTF("creating Server object\n");

	paris::Server server;
	server.start_server();

	DEBUG_PRINTF("starting server\n");

	DEBUG_PRINTF("creating Service's\n");
	paris::ExampleService service1;
	paris::ExampleService service2;

	DEBUG_PRINTF("adding Service's\n");
	server.add_service(service1);
	server.add_service(service2);

	DEBUG_PRINTF("sending paris_message_t's to services\n");
	sleep(1);
	paris::paris_message_t message;
	message.uid = 420;
	message.service_id = service1.get_service_id();
	server.send_message(message);
	sleep(1);
	message.uid = 69;
	message.service_id = service2.get_service_id();
	server.send_message(message);
	sleep(1);

	DEBUG_PRINTF("stopping server\n");
	server.stop_server();
	sleep(1);

	return 0;
}