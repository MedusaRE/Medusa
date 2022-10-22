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

#ifndef PARIS_PARIS_HPP
#define PARIS_PARIS_HPP

#include <condition_variable>
#include "message.hpp"
#include <thread>
#include <vector>
#include <mutex>
#include <queue>

#define THREAD_WAIT() do { std::this_thread::sleep_for(std::chrono::nanoseconds(1)); } while (0)

namespace paris {
	class Service {
		public:
			virtual bool send_message(paris_message_t message) = 0;
			virtual std::thread get_backing_thread() = 0;
			virtual uint64_t get_service_id() = 0;
		protected:
			std::thread thread;
	};

	class ExampleService : public Service {
		public:
			ExampleService();
			static void service_mainloop(ExampleService* _this);
			bool send_message(paris_message_t message);
			std::thread get_backing_thread();
			uint64_t get_service_id();
		protected:
			std::queue<paris_message_t> queue;
			std::condition_variable cv;
			std::thread thread;
			std::mutex mtx;
			uint64_t id;
			bool run;
	};

	class Server {
		public:
			bool start_server();
			bool stop_server();
			std::thread get_backing_thread();

			static void server_mainloop(Server* _this);
			static bool queue_available(Server* _this);

			bool add_service(Service& service);
			bool send_message(paris_message_t message);
			bool remove_service(Service& service);
			bool remove_service(uint64_t service);
		protected:
			std::queue<paris_message_t> queue;
			std::vector<Service*> services;
			std::condition_variable cv;
			std::thread thread;
			std::mutex mtx;
			bool run;
	};
}

#endif
