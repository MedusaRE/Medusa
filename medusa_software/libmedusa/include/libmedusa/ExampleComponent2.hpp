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

#ifndef LIBMEDUSA_EXAMPLE_COMPONENT2_HPP
#define LIBMEDUSA_EXAMPLE_COMPONENT2_HPP

#include <libmedusa/Component.hpp>
#include <libmedusa/libmedusa.hpp>
#include <string>

#define EXAMPLE_COMPONENT2_TYPE 0x1

namespace libmedusa {
	/**
	 *	@brief A second example Component to demonstrate a Component interface.
	 */
	class ExampleComponent2 : public Component {
		public:
			component_definition_t get_component_definition();

			/**
			 *	@brief Get a random integer from this Component as a string.
			 *
			 *	@returns A random integer generated by this Component as a
			 *			 string.
			 */
            std::string get_component_string_output();
	};
}

#endif