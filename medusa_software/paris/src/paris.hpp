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

#include "message.hpp"
#include <thread>

namespace paris {
	class Service {
		public:
			virtual bool send_message(paris_message_t message) = 0;
			virtual std::thread get_backing_thread() = 0;
			virtual uint64_t get_service_id() = 0;
		protected:
			std::thread thread;
	};

	class Server {
		public:
			bool start_server();
			std::thread get_backing_thread();

			bool add_service(Service& service);
			bool send_message(paris_message_t message);
			bool remove_service(Service& service);
			bool remove_service(uint64_t service);
		protected:
			std::thread thread;
	};
}

#endif
