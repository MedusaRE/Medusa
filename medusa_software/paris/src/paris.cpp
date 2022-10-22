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

#include "message.hpp"
#include "paris.hpp"
#include <chrono>
#include <cstdio>
#include <thread>
#include <queue>

using namespace paris;

std::queue<paris_message_t> Server::queue;

void Server::server_mainloop() {
	paris_message_t message;

	while (1) {
		while (Server::queue.empty()) {
			std::this_thread::sleep_for(std::chrono::nanoseconds(1));
		}

		message = Server::queue.front();
		Server::queue.pop();

		printf("%d\n", message.uid);
	}

	__builtin_unreachable();
}

bool Server::send_message(paris_message_t message) {
	Server::queue.push(message);

	return true;
}

bool Server::start_server() {
	this->thread = std::thread(Server::server_mainloop);

	return true;
}