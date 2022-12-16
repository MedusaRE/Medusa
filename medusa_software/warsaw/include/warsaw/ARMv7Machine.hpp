/**
 *  @file
 *  @author  spv <spv@spv.sh>
 * 
 *  @section LICENSE
 * 
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of version 2 of the GNU General Public License as
 *  published by the Free Software Foundation.
 * 
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *  General Public License for more details at
 *  https://www.gnu.org/copyleft/gpl.html
 * 
 *  @section DESCRIPTION
 * 
 *  The Machine class represents a generic machine that a piece of software
 *  utilizing libmedusa can interface with.
 */

#ifndef WARSAW_ARMV7_MACHINE_HPP
#define WARSAW_ARMV7_MACHINE_HPP

#include <libmedusa/ARMv7Machine.hpp>
#include <libmedusa/Machine.hpp>
#include <warsaw/Machine.hpp>
#include <paris/message.hpp>
#include <paris/paris.hpp>

namespace warsaw {
	/**
	 *	@brief A Paris service for libmedusa::Machine.
	 */
	class ARMv7Machine : public paris::ServiceListener {
		public:
			virtual bool process_message(paris::paris_message_t message,
										 paris::Server* server);

			virtual bool builtin_init(paris::Server* server);
		protected:
			libmedusa::ARMv7Machine armv7_machine;
	};
}

#endif