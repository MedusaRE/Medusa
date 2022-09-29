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
 *  The ExampleComponent2 class implements the Component generic class to
 *  provide a second example component for testing Component implementations.
 */

#include <libmedusa/ExampleComponent2.hpp>
#include <libmedusa/Component.hpp>
#include <libmedusa/libmedusa.hpp>
#include <sstream>

using namespace libmedusa;

component_definition_t ExampleComponent2::get_component_definition() {
	component_definition_t component_definition;

	component_definition.component_id = 0xfeedfacefeedfacf;
	component_definition.component_type = EXAMPLE_COMPONENT2_TYPE;
	component_definition.description = "A second example Component to test implementations of the Component class.";
	component_definition.name = "Example Component2";

	return component_definition;
}

std::string ExampleComponent2::get_component_string_output() {
	std::stringstream ss;
	
	ss << rand();
	ss << "str";

	return ss.str();
}