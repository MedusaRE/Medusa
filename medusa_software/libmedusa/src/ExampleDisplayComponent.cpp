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
 *  The ExampleDisplayComponent class implements the Component generic class
 *  to provide an example component for testing software that interfaces with
 *  display Components.
 */

#include <libmedusa/ExampleDisplayComponent.hpp>
#include <libmedusa/Component.hpp>
#include <libmedusa/libmedusa.hpp>

using namespace libmedusa;

component_definition_t ExampleDisplayComponent::get_component_definition() {
	component_definition_t component_definition;

	component_definition.component_id = 0xfeedfacffeedface;
	component_definition.component_type = DISPLAY_COMPONENT_TYPE;
	component_definition.description = "An example Component to test implementations of the Component class.";
	component_definition.name = "Example Display Component";

	return component_definition;
}

ExampleDisplayComponent::ExampleDisplayComponent() {
	this->bitmap.width = 320;
	this->bitmap.height = 240;
	this->bitmap.pixels = (pixel_t*)calloc(this->bitmap.width * this->bitmap.height, sizeof(pixel_t));
}

bitmap_t ExampleDisplayComponent::get_component_display_output() {
	for (int x = 0; x < this->bitmap.width; x++) {
		for (int y = 0; y < this->bitmap.height; y++) {
			this->bitmap.pixels[(y * this->bitmap.width) + x].red = ((x) % 256);
			this->bitmap.pixels[(y * this->bitmap.width) + x].green = ((y) % 256);
			this->bitmap.pixels[(y * this->bitmap.width) + x].blue = ((x + y) % 256);
		}
	}

	return this->bitmap;
}