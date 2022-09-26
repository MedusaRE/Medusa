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

#ifndef PARIS_MESSAGE_H
#define PARIS_MESSAGE_H

#include <cstdint>

namespace paris {
	/**
	 *  @brief	A structure representing a message in the Paris system.
	 */
	typedef struct {
		uint32_t len;			 /**< The length of this message, *including the sid and uid* */
		uint32_t sid;			 /**< The ID of the session that sent this message. */
		uint32_t uid;			 /**< The UID of the user that sent this message. */
		uint8_t msg_contents[0]; /**< A variable-length array containing the contents of this message. */
	} paris_message_t;
}

#endif