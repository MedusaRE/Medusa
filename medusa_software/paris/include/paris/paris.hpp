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
	class Server;
	class Service;
	class ExampleService;
	class ServiceListener;
	class ExampleService2;

	/**
	 *	@brief A structure containing a paris_message_t & Server.
	 */
	typedef struct {
		paris_message_t message;	/**< The message that was sent. */
		Server* server;				/**< The Server that this message was sent
										 with. */
	} paris_message_and_server_t;

	/**
	 *	@brief An abstract class representing an interface for Paris services.
	 */
	class Service {
		public:
			/**
			 * 	@brief Send a paris_message_t to this Service.
			 *
			 * 	@param message The paris_message_t to be sent.
			 * 	@param server The Server with which this message was sent.
			 * 	@return true  Success.
			 * 	@return false Fail.
			 */
			virtual bool send_message(paris_message_t message, Server* server) = 0;

			/**
			 *	@brief Get the std::thread that this Service is "backed" by.
			 *
			 *	@return std::thread The std::thread that this Service is
			 			"backed" by.
			 */
			virtual std::thread get_backing_thread() = 0;

			/**
			 *	@brief Get the ID of this Service.
			 *
			 *	@return uint64_t The ID of this Service.
			 */
			virtual uint64_t get_service_id() = 0;

			/**
			 *	@brief Stop this Service.
			 *
			 *	@return true  Success.
			 *	@return false Fail.
			 */
			virtual bool stop_service() = 0;
		protected:
			std::thread thread;
	};

	/**
	 *	@brief A semi-abstract class representing and implementing code for
	 *		   listening to messages and processing them.
	 */
	class ServiceListener : public Service {
		public:
			ServiceListener();
			~ServiceListener();

			bool send_message(paris_message_t message, Server* server);
			std::thread get_backing_thread();
			uint64_t get_service_id();
			bool stop_service();

			/**
			 *	@brief The "mainloop" for this Service &mdash; a function that
			 *		   listens to the queue and sends the message(s) to
			 *		   process_message.
			 *
			 *	@param _this The ServiceListener object that we should use
			 *				 &mdash; service_mainloop must be static for
			 *				 std::thread usage, so we need to pass this to
			 *				 access member functions and variables.
			 */
			static void service_mainloop(ServiceListener* _this);

			/**
			 *	@brief Make this Service process a paris_message_t.
			 *
			 *	@param message The paris_message_t to be processed.
			 *	@param server The Server this message was sent with.
			 *
			 *	@return true  Success.
			 *	@return false Fail.
			 */
			virtual bool process_message(paris_message_t message, Server* server);

			/**
			 *	@brief An override-able function to initialize Service-specific
			 *		   data / objects. This is called when the service is added
			 *		   to a Server. (or really, when it receives a
			 *		   PARIS_INIT_MSG message.)
			 *
			 *	@param	server The Server on which this Service was added to. 
			 *
			 *	@return true  Success.
			 *	@return false Fail.
			 */
			virtual bool builtin_init(paris::Server* server);
		protected:
			std::queue<paris_message_and_server_t> queue;
			std::condition_variable cv;
			std::thread thread;
			std::mutex mtx;
			uint64_t id;
			bool run;
	};

	/**
	 *	@brief An example Service based on ServiceListener.
	 */
	class ExampleService : public ServiceListener {
		public:
			virtual bool process_message(paris_message_t message, Server* server);
	};

	/**
	 *	@brief A service that dumps the msg_contents of paris_message_t's that
	 *		   it receives to stdout.
	 */
	class DumpMsgContentsToSTDOUTService : public ServiceListener {
		public:
			virtual bool process_message(paris_message_t message, Server* server);
	};

	typedef struct {
		uint64_t session_id;
		uint64_t uid;
		uint64_t cookie[4];
	} paris_session_t;

	/**
	 *	@brief A class implementing a Server for the Paris backend.
	 */
	class Server {
		public:
			/**
			 *	@brief Start this Server.
			 *
			 *	@return true  Success.
			 *	@return false Fail.
			 */
			bool start_server();

			/**
			 *	@brief Stop this Server.
			 *
			 *	@return true  Success.
			 *	@return false Fail.
			 */
			bool stop_server();

			/**
			 *	@brief Get the std::thread that this Server is "backed" by.
			 *
			 *	@return std::thread The std::thread that this Server is "backed"
			 *			by.
			 */
			std::thread get_backing_thread();


			/**
			 *	@brief The "mainloop" for this Server &mdash; a function that
			 *		   listens to the queue and sends the message(s) to
			 *		   the appropriate Service's.
			 *
			 *	@param _this The Server object that we should use &mdash;
			 *				 service_mainloop must be static for std::thread
			 *				 usage, so we need to pass this to access member
			 *				 functions and variables.
			 */
			static void server_mainloop(Server* _this);
			static bool queue_available(Server* _this);

			/**
			 *	@brief Add/connect a Service to this Server.
			 *
			 *	@param service The Service to add.
			 *
			 *	@return true  Success.
			 *	@return false Fail.
			 */
			bool add_service(Service& service);

			/**
			 *	@brief Send a paris_message_t to a Service on this Server.
			 *
			 *	@param message The message to send.
			 *	@return true  Success.
			 *	@return false Fail.
			 */
			bool send_message(paris_message_t message);

			/**
			 *	@brief Remove/disconnect a Service from this Server.
			 *
			 *	@param service The Service to remove/disconnect.
			 *	@return true  Success.
			 *	@return false Fail.
			 */
			bool remove_service(Service& service);

			/**
			 *	@brief Remove/disconnect a Service from this Server.
			 *
			 *	@param service The Service to remove/disconnect.
			 *	@return true  Success.
			 *	@return false Fail.
			 */
			bool remove_service(uint64_t service);

			/**
			 *	@brief Get an std::vector of pointers to all Service's connected
			 *		   to this Server.
			 *
			 *	@return std::vector<Service*> An std::vector of pointers to all
			 *			Service's connected to this Server.
			 */
			std::vector<Service*> get_services();
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
