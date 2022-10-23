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
#include <random>
#include <string>
#include <thread>
#include <vector>
#include <mutex>
#include <queue>
#include "lib.h"

using namespace paris;

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
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<uint64_t> dis;

	this->id = dis(gen);
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

bool ServiceListener::process_message(paris_message_t message, Server* server) {
	DEBUG_PRINTF("%lx: %d\n", message.service_id, message.uid);

	return true;
}

bool ExampleService::process_message(paris_message_t message, Server* server) {
	DEBUG_PRINTF("%lx: %d\n", message.service_id, message.uid);

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
			paris_message_t reply;
			reply.len = 8;
			reply.msg_contents = (uint8_t*)calloc(1, 8);
		
			*(uint64_t*)reply.msg_contents = medusa_rand();

			for (Service*& service : _this->services) {
				if (service->get_service_id() == message.service_by) {
					service->send_message(reply, _this);
				}
			}

			continue;
		}

		for (Service*& service : _this->services) {
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