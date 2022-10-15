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

#ifndef VIENNA_VIENNA_HPP
#define VIENNA_VIENNA_HPP

#include <libmedusa/ARMv7Machine.hpp>
#include <libmedusa/libmedusa.hpp>

namespace vienna {
	/*
	 *  this is simply meant to declare the `vienna` namespace.
	 */

	/**
	 *	@brief An enum representing an opcode for Vienna's Intermediate
	 *		   Representation (IR).
	 */
	typedef enum {
		NOP,		/**< A no-op, an instruction that does nothing. */
	} ir_opcode_t;

	typedef struct {
		ir_opcode_t ir_opcode;
	} ir_t;
}

#endif
