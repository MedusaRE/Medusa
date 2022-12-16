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
#include <paris/message.hpp>
#include <paris/paris.hpp>
#include <chrono>
#include <cstdio>
#include <random>
#include <string>
#include <thread>
#include <vector>
#include <mutex>
#include <queue>
#include "lib.h"

using namespace paris;

/*
 *	Basically, this is how/why this function/method works.
 *
 *	We could just spin-check on a separate thread, but that would be pretty
 *	inefficient. Instead, we use an std::condition_variable. The need for the
 *	(relatively) complex lambda function is so that we can cleanly shutdown the
 *	Paris server when we're done -- and not necessarily have to send another
 *	message to do so. The ServiceListener::stop_service function/method sets
 *	this->run to false, and then notifies `cv`, meaning that it will be able to
 *	cleanly shut down the service.
 */
void ServiceListener::service_mainloop(ServiceListener* _this) {
	paris_message_and_server_t message;

	while (_this->run) {
		std::unique_lock<std::mutex> lck(_this->mtx);
		while (_this->queue.empty()) {
			_this->cv.wait(lck, [&_this]{ return (_this->queue.size() != 0) || !_this->run; });

			if (!_this->run) {
				break;
			}
		}

		message = _this->queue.front();
		_this->queue.pop();

		if (message.message.message_type == PARIS_INIT_MSG) {
			_this->builtin_init(message.server);
			continue;
		}

		_this->process_message(message.message, message.server);
	}

	DEBUG_PRINTF("%lx done\n", _this->get_service_id());
}

bool ServiceListener::send_message(paris_message_t message, Server* server) {
	paris_message_and_server_t tmp = {message, server};

	this->queue.push(tmp);
	this->cv.notify_one();

	return true;
}

bool ServiceListener::stop_service() {
	this->run = false;
	this->cv.notify_one();

	return true;
}

std::thread ServiceListener::get_backing_thread() {
	return std::move(this->thread);
}

ServiceListener::ServiceListener() {
	this->id = medusa_rand();
	this->run = true;

	this->thread = std::thread(ServiceListener::service_mainloop, this);
	this->thread.detach();
}

ServiceListener::~ServiceListener() {
	this->run = false;
	this->cv.notify_one();
}

uint64_t ServiceListener::get_service_id() {
	return this->id;
}

bool ServiceListener::builtin_init(paris::Server* server) {
	return true;
}

bool ServiceListener::process_message(paris_message_t message, Server* server) {
	DEBUG_PRINTF("%lx: %lu\n", message.service_id, message.uid);

	return true;
}

bool ExampleService::process_message(paris_message_t message, Server* server) {
	DEBUG_PRINTF("%lx: %lu\n", message.service_id, message.uid);

	if (!server) {
		return false;
	}

	return true;
}

bool DumpMsgContentsToSTDOUTService::process_message(paris_message_t message, Server* server) {
	std::string s;

	if (!message.msg_contents) {
		return false;
	}

	if (message.len >= 1) {
		s += string_format("%02x", message.msg_contents[0]);
	}

	if (message.len >= 2) {
		s += string_format(" %04x", U8X2_TO_U16(message.msg_contents[1], message.msg_contents[0]));
	}

	if (message.len >= 4) {
		s += string_format(" %08x", U8X4_TO_U32(message.msg_contents[3], message.msg_contents[2],
												message.msg_contents[1], message.msg_contents[0]));
	}

	if (message.len >= 8) {
		s += string_format(" %016lx", U8X8_TO_U64(message.msg_contents[7], message.msg_contents[6],
												  message.msg_contents[5], message.msg_contents[4],
												  message.msg_contents[3], message.msg_contents[2],
												  message.msg_contents[1], message.msg_contents[0]));
	}

	s += " (";

	for (int i = 0; i < message.len; i++) {
		s += string_format("%02x, ", message.msg_contents[i]);
	}

	s = s.substr(0, s.length() - 2) + ")";

	DEBUG_PRINTF("%s\n", s.c_str());

	return true;
}

bool Server::queue_available(Server* _this) {
	return !_this->queue.empty();
}

void Server::server_mainloop(Server* _this) {
	paris_message_t message;

	while (_this->run) {
		std::unique_lock<std::mutex> lck(_this->mtx);
		while (_this->queue.empty()) {
			_this->cv.wait(lck, [&_this]{ return (_this->queue.size() != 0) || !_this->run; });

			if (!_this->run) {
				break;
			}
		}

		message = _this->queue.front();
		_this->queue.pop();

		if (message.service_id == PARIS_SERVER_SERVICE_ID) {
			/*
			 *	TODO: use something better than `calloc` for things like this!
			 */
			paris_session_t* session = (paris_session_t*)calloc(1, sizeof(paris_session_t));
			paris_message_t reply;

			session->session_id = medusa_rand();
			session->uid = -1;

			for (int i = 0; i < (sizeof(session->cookie) / sizeof(session->cookie[0])); i++) {
				session->cookie[i] = medusa_rand();
			}

			reply.len = sizeof(paris_session_t);
			reply.msg_contents = (uint8_t*)session;

			for (Service*& service : _this->services) {
				if (service->get_service_id() == message.service_by) {
					service->send_message(reply, _this);
				}
			}

			continue;
		}

		for (Service*& service : _this->services) {
			/*
			 *	segfaults be damned!
			 */
			if (!service) {
				continue;
			}

			if (service->get_service_id() == message.service_id) {
				service->send_message(message, _this);
			}
		}
	}

	for (Service*& service : _this->services) {
		DEBUG_PRINTF("stopping %lx\n", service->get_service_id());
		service->stop_service();
	}
}

bool Server::add_service(Service& service) {
	this->services.push_back(&service);

	paris_message_t msg;

	msg.message_type = PARIS_INIT_MSG;

	service.send_message(msg, this);
	return true;
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

	this->cv.notify_one();

	return true;
}

std::vector<Service*> Server::get_services() {
	return this->services;
}
