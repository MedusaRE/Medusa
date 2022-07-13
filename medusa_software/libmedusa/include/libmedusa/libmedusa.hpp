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

#ifndef LIBMEDUSA_HPP
#define LIBMEDUSA_HPP

#include <cstdint>
#include <string>

#define XP_PROT_READ (1 << 0)
#define XP_PROT_WRITE (1 << 1)
#define XP_PROT_EXEC (1 << 2)
#define MNEMONIC_SIZE 32

#define XP_FLAG_THUMB (1 << 0)

namespace libmedusa {
	/*
	 *  empty
	 */
}

#include <libmedusa/Machine.hpp>
#include <capstone/capstone.h>
#include <keystone/keystone.h>
#include <unicorn/unicorn.h>

#endif