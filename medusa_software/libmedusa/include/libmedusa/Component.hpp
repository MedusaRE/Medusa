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
 *  The Component class is an object describing a generic hardware component
 *  like a CPU, GPU, display out, storage, etc.
 */

#ifndef LIBMEDUSA_COMPONENT_HPP
#define LIBMEDUSA_COMPONENT_HPP

#include <libmedusa/libmedusa.hpp>
#include <string>

namespace libmedusa {
	typedef struct {
		std::string name;
		std::string description;
		uint64_t component_type;
		uint64_t component_id;
	} component_definition_t;

	class Component {
		public:
			virtual component_definition_t get_component_definition() = 0;
	};
}

#endif