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

#include <libmedusa/DisplayOutput.hpp>
#include <libmedusa/Component.hpp>
#include <libmedusa/libmedusa.hpp>
#include <string>

#define DISPLAY_COMPONENT_TYPE 0x2

namespace libmedusa {
	/**
	 *	@brief A class representing the standard libmedusa API for interacting
	 *		   with bitmap-type (virtualized) displays.
	 */
	class ExampleDisplayComponent : public DisplayOutput {
		public:
			/**
			 *	@brief The constructor for ExampleDisplayComponent.
			 */
			ExampleDisplayComponent();

			/**
			 *	@brief Get the definition of this Component.
			 *
			 *	@returns The component definition as a component_definition_t.
			 */
			component_definition_t get_component_definition();

			/**
			 *	@brief Get the display output from this Component.
			 *
			 *	@returns The current contents of the display/framebuffer as a
			 *			 bitmap_t.
			 */
			bitmap_t get_component_display_output();
		private:
			bitmap_t bitmap;
	};
}

#endif