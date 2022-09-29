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
 *  The DisplayOutput class implements the Component generic class
 *  to provide an API to implement for Display output Components.
 */

#ifndef LIBMEDUSA_DISPLAY_OUTPUT_HPP
#define LIBMEDUSA_DISPLAY_OUTPUT_HPP

#include <libmedusa/Component.hpp>
#include <libmedusa/libmedusa.hpp>
#include <string>

#define DISPLAY_COMPONENT_TYPE 0x2

namespace libmedusa {
	/**
	 *  @brief A structure representing an RGB-colored pixel.
	 */
	typedef struct {
		uint8_t red;   /**< The red component of the pixel. */
		uint8_t green; /**< The green component of the pixel. */
		uint8_t blue;  /**< The blue component of the pixel. */
	} pixel_t;

	/**
	 *	@brief A structure representing a bitmap (read: uncompressed) image.
	 */
	typedef struct {
		uint32_t width;  /**< The width of the image. */
		uint32_t height; /**< The height of the image. */
		pixel_t* pixels; /**< A pointer to pixel_t's representing the contents
							  of this image. */
	} bitmap_t;

	/**
	 *	@brief A class representing the standard libmedusa API for interacting
	 *		   with bitmap-type (virtualized) displays.
	 */
	class DisplayOutput : public Component {
		public:
			/**
			 *	@brief Get the definition of this Component.
			 *
			 *	@returns The component definition as a component_definition_t.
			 */
			virtual component_definition_t get_component_definition() = 0;

			/**
			 *	@brief Get the display output from this Component.
			 *
			 *	@returns The current contents of the display/framebuffer as a
			 *			 bitmap_t.
			 */
			virtual bitmap_t get_component_display_output() = 0;
	};
}

#endif