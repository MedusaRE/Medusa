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

#include <condition_variable>
#include "message.hpp"
#include "paris.hpp"
#include <chrono>
#include <cstdio>
#include <thread>
#include <mutex>
#include <queue>

using namespace paris;

bool Server::queue_available(Server* _this) {
	return !_this->queue.empty();
}

void Server::server_mainloop(Server* _this) {
	paris_message_t message;

	while (_this->run) {
		std::unique_lock<std::mutex> lck(_this->mtx);
		while (_this->queue.empty()) {
			_this->cv.wait(lck, [&_this]{ return _this->queue.size() != 0; });
		}

		message = _this->queue.front();
		_this->queue.pop();

		printf("%d\n", message.uid);
	}

	__builtin_unreachable();
}

bool Server::send_message(paris_message_t message) {
	this->queue.push(message);
	this->cv.notify_one();

	return true;
}

bool Server::start_server() {
	this->run = true;

	this->thread = std::thread(Server::server_mainloop, this);
	this->thread.detach();

	return true;
}

bool Server::stop_server() {
	this->run = false;

	return true;
}