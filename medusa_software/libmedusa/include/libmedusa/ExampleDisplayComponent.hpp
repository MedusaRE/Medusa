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

#ifndef LIBMEDUSA_EXAMPLE_DISPLAY_COMPONENT_HPP
#define LIBMEDUSA_EXAMPLE_DISPLAY_COMPONENT_HPP

#include <libmedusa/Component.hpp>
#include <libmedusa/libmedusa.hpp>
#include <string>

#define DISPLAY_COMPONENT_TYPE 0x2

namespace libmedusa {
	typedef struct {
		uint8_t red;
		uint8_t green;
		uint8_t blue;
	} pixel_t;

	typedef struct {
		uint32_t width;
		uint32_t height;
		pixel_t* pixels;
	} bitmap_t;

	class ExampleDisplayComponent : public Component {
		public:
			ExampleDisplayComponent();
			component_definition_t get_component_definition();
			bitmap_t get_component_display_output();
		private:
			bitmap_t bitmap;
	};
}

#endif