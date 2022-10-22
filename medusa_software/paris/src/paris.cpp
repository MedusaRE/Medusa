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
#include <thread>
#include <vector>
#include <mutex>
#include <queue>
using namespace paris;

void ExampleService::service_mainloop(ExampleService* _this) {
	paris_message_t message;

	while (_this->run) {
		std::unique_lock<std::mutex> lck(_this->mtx);
		while (_this->queue.empty()) {
			_this->cv.wait(lck, [&_this]{ return _this->queue.size() != 0; });
		}

		message = _this->queue.front();
		_this->queue.pop();

		printf("A: 0x%lx 0x%lx\n", message.service_id, _this->get_service_id());
	}
}

bool ExampleService::send_message(paris_message_t message) {
	this->queue.push(message);
	this->cv.notify_one();

	return true;
}

std::thread ExampleService::get_backing_thread() {
	return std::move(this->thread);
}

ExampleService::ExampleService() {
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<uint64_t> dis;

	this->id = dis(gen);
	this->run = true;

	this->thread = std::thread(ExampleService::service_mainloop, this);
	this->thread.detach();
}

uint64_t ExampleService::get_service_id() {
	return this->id;
}

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
		for (Service*& service : _this->services) {
			printf("%lx %lx\n", service, message.service_id);
			if (service->get_service_id() == message.service_id) {
				service->send_message(message);
			}
		}
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

	return true;
}