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
	/**
	 *	@brief A structure representing basic information about a Component.
	 */
	typedef struct {
			std::string name;			/**< The name of this Component type,
											 e.g. "SoundOutput". */
			std::string description;	/**< A short description of this
											 Component type, e.g. "Sound
											 output from the C64" */
			std::string component_name; /**< The name of this particular
											 Component, e.g. "John's C64's
											 Sound Output". */
			std::string component_description; /**< A short description of this
													particular component, e.g.
												  "The sound outputted by John's
													C64." */
			uint64_t component_api_type; /**< A 64-bit number unique to all
										   Components that share an API,
										   e.g a unique number for
										   SoundOutput, shared with
										   SIDSoundOutput, or a unique
										   number for DisplayOutput, shared
										   with VIC2DisplayOutput. */
			uint64_t component_type;	 /**< A 64-bit number unique to this
											  type of Component, e.g. a unique
											  number for SoundOutput,
											  SIDSoundOutput, DisplayOutput,
											  and VIC2DisplayOutput. */
			uint64_t component_id;		 /**< A unique id for this particular
											  Component *instance*, 2
											  different SIDSoundOutput
											  Components should have different
											  ids. */
	} component_definition_t;

	/**
	 *	@brief A generic class representing a Component that an application
	 *	   utilizing libmedusa could interface with.
	 */
	class Component {
		public:
			/**
			 *	@brief Get the definition of this Component.
			 *
			 *	@returns The component definition as a component_definition_t.
			 */
			virtual component_definition_t get_component_definition() = 0;
	};
} //  namespace libmedusa

#endif