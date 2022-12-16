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
 *  This file is a generic file that includes necessary headers for the rest of
 *  libmedusa, defines some preprocessor \#define's, and has a namespace section
 *  for the libmedusa namespace.
 */

/*
 *	TODO:
 *		  * implement more component APIs and example components to go along
 *			with them.
 */

#ifndef LIBMEDUSA_HPP
#define LIBMEDUSA_HPP

#include <cstdint>
#include <string>
#include <vector>

#define XP_PROT_READ  (1 << 0)
#define XP_PROT_WRITE (1 << 1)
#define XP_PROT_EXEC  (1 << 2)
#define MNEMONIC_SIZE  32

#define XP_FLAG_THUMB (1 << 0)
#define XP_FLAG_NOREGNAME (1 << 1)
#define XP_FLAG_SKIPDATA (1 << 2)

namespace libmedusa {
	/*
	 *  empty
	 */
}

#include <libmedusa/Machine.hpp>
#include <capstone/capstone.h>
#include <keystone/keystone.h>
#include <unicorn/unicorn.h>

namespace libmedusa {
	bool destroy_insn_t(libmedusa::insn_t insn);
	bool destroy_insn_t_vector(std::vector<libmedusa::insn_t> insns);
}

#endif