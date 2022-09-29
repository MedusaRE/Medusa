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
 *  The ExampleComponent class implements the Component generic class to provide
 *  an example component for testing Component implementations.
 */

#ifndef LIBMEDUSA_EXAMPLE_COMPONENT_HPP
#define LIBMEDUSA_EXAMPLE_COMPONENT_HPP

#include <libmedusa/Component.hpp>
#include <libmedusa/libmedusa.hpp>
#include <string>

#define EXAMPLE_COMPONENT_TYPE 0x0

namespace libmedusa {
	class ExampleComponent : public Component {
		public:
			component_definition_t get_component_definition();
            int get_component_int_output();
	};
}

#endif