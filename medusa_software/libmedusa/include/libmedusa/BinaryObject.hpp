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

#ifndef BINARY_OBJECT_HPP
#define BINARY_OBJECT_HPP

#include <libmedusa/libmedusa.hpp>

namespace libmedusa {
	typedef struct {
		std::string			  name;
		uint64_t			  addr;
		uint64_t			  size;
		libmedusa::mem_prot_t prot;
	} section_desc_t;

	typedef struct {
		libmedusa::section_desc_t section_desc;
		std::vector<uint8_t>	  data;
	} section_t;

	class BinaryObject {
		public:
			std::vector<libmedusa::section_t> get_section_list() = 0;
	};
}

#include <LIEF/LIEF.hpp>

#endif