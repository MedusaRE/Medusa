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

#ifndef PARIS_MESSAGE_HPP
#define PARIS_MESSAGE_HPP

#include <cstdint>
#define PARIS_SERVER_SERVICE_ID -1

namespace paris {
	typedef enum {
		REGISTER_SESSION,
		CLOSE_SESSION
	} paris_message_type_t;

	/**
	 *  @brief	A structure representing a message in the Paris system.
	 */
	typedef struct {
		uint32_t len;			 /**< The length of #msg_contents. */
		uint32_t version;		 /**< The version of the Paris standard that
									  this message uses. Useful for determining
									  where #msg_contents starts and other
									  fields end. */
		uint32_t sid;			 /**< The ID of the session that sent this
									  message. */
		uint32_t uid;			 /**< The UID of the user that sent this
									  message. */
		uint64_t cookie[4];		 /**< Secret session cookie - a unique 256-bit
									  number to identify that a message was
									  indeed sent by who it claims to have been
									  sent by. */
		uint64_t service_id;	 /**< The ID of the Service this message should
									  be forwarded to. */

		uint64_t service_by;	 /**< The ID of the Service this message was
									  sent by. */

		paris_message_type_t message_type; /**< The type of message. */

		uint8_t *msg_contents;	 /**< A variable-length array containing the
									  contents of this message. It is assumed
									  that #msg_contents has a length of
									  #len. */
	} paris_message_t;
}

#endif