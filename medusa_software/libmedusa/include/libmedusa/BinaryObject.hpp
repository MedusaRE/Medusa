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
 *  The BinaryObject class is a general object describing a binary/executable
 *  object like an ELF, PE, Mach-O binary, a shared object, and objects like
 *  that.
 */

#ifndef BINARY_OBJECT_HPP
#define BINARY_OBJECT_HPP

#include <libmedusa/libmedusa.hpp>

namespace libmedusa {
	/**
	 *  @brief A structure representing a section of a binary object.
	 */
	typedef struct {
		std::string			  name; /**< The name of this section, e.g. _TEXT */
		uint64_t			  addr; /**< The address in memory that this section
										 is at. */
		uint64_t			  size; /**< The size in memory of this section,
										 once mapped. */
		libmedusa::mem_prot_t prot; /**< The protections of the memory this
										 section contains. */
	} section_desc_t;

	/**
	 *	@brief A structure representing a section description, and the data it
	 *		   contains.
	 */
	typedef struct {
		libmedusa::section_desc_t  section_desc; /**< A description of this
													  section. */
		uint8_t					  *data;		 /**< A pointer to the data of
													  this section. Set to NULL
													  if the section contains no
													  data. */
	} section_t;

	/**
	 *	@brief A generic class representing a binary object, e.g. ELF, PE, or
	 *		   Mach-O.
	 */
	class BinaryObject {
		public:
			/**
			 *  @brief Obtain all of the sections in this binary object as an
			 *  std::vector of section_t's.
			 * 
			 *  @return std::vector of all sections as section_t's.
			 */
			virtual std::vector<libmedusa::section_t> get_section_list() = 0;
	};
}

#include <LIEF/LIEF.hpp>

#endif