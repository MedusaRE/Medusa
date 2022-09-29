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

#include <libmedusa/ExampleComponent.hpp>
#include <libmedusa/Component.hpp>
#include <libmedusa/libmedusa.hpp>

using namespace libmedusa;

component_definition_t ExampleComponent::get_component_definition() {
    component_definition_t component_definition;

    component_definition.component_id = 0xfeedfacefeedface;
    component_definition.component_type = 0x0;
    component_definition.description = "An example Component to test implementations of the Component class.";
    component_definition.name = "Example Component";

    return component_definition;
}