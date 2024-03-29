/*
 *  Copyright (C) 2023, w212 research. <contact@w212research.com>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of version 2 of the GNU General Public License as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef ELF_HPP
#define ELF_HPP

#include "XParse.hpp"

#include <cstdint>
#include <string>

namespace XParse {
	namespace ELF {
		typedef enum {
			ELF_32				  = 1,
			ELF_64				  = 2,
			ELF_INVALID_ADDR_SIZE = 3,
		} raw_elf_addr_size_t;

		typedef enum {
			ELF_LITTLE_ENDIAN	   = 1,
			ELF_BIG_ENDIAN		   = 2,
			ELF_INVALID_ENDIANNESS = 3,
		} raw_elf_endianness_t;

		typedef enum {
			ELF_ABI_SYSTEM_V = 0x0,
			ELF_ABI_HP_UX	 = 0x1,
			ELF_ABI_NETBSD	 = 0x2,
			ELF_ABI_LINUX	 = 0x3,
			ELF_ABI_HURD	 = 0x4,
			ELF_ABI_INVALID	 = 0x5,
			ELF_ABI_SOLARIS	 = 0x6,
			ELF_ABI_AIX		 = 0x7,
			ELF_ABI_IRIX	 = 0x8,
			ELF_ABI_FREEBSD	 = 0x9,
			ELF_ABI_TRU64	 = 0xa,
			ELF_ABI_MODESTO	 = 0xb,
			ELF_ABI_OPENBSD	 = 0xc,
			ELF_ABI_OPENVMS	 = 0xd,
			ELF_ABI_NONSTOP	 = 0xe,
			ELF_ABI_AROS	 = 0xf,
			ELF_ABI_FENIXOS	 = 0x10,
			ELF_ABI_CLOUDABI = 0x11,
			ELF_ABI_OPENVOS	 = 0x12,
			ELF_ABI__END,
		} raw_elf_abi_t;

		typedef enum {
			ELF_OBJ_TYPE_UNKNOWN			= 0x0,
			ELF_OBJ_TYPE_REL				= 0x1,
			ELF_OBJ_TYPE_EXEC				= 0x2,
			ELF_OBJ_TYPE_DYN				= 0x3,
			ELF_OBJ_TYPE_CORE				= 0x4,
			ELF_OBJ_TYPE_INVALID			= 0x5,
			ELF_OBJ_TYPE_RESERVED_OS		= 0xfe00,
			ELF_OBJ_TYPE_RESERVED_PROCESSOR = 0xff00,
			ELF_OBJ_TYPE_END				= 0xffff,
		} raw_elf_obj_type_t;

		typedef enum {
			ELF_ISA_UNSPECIFIED		= 0x0,
			ELF_ISA_ATT_WE_32100	= 0x1,
			ELF_ISA_SPARC			= 0x2,
			ELF_ISA_X86				= 0x3,
			ELF_ISA_M68000			= 0x4,
			ELF_ISA_M88000			= 0x5,
			ELF_ISA_MCU				= 0x6, //  shitty movie series
			ELF_ISA_80860			= 0x7,
			ELF_ISA_MIPS			= 0x8,
			ELF_ISA_SYSTEM_370		= 0x9,
			ELF_ISA_MIPS_RS3000_LE	= 0xa,
			ELF_ISA_RESERVED		= 0xb,
			ELF_ISA_HP_PA_RISC		= 0xe,
			ELF_ISA_80960			= 0x13,
			ELF_ISA_PPC				= 0x14,
			ELF_ISA_PPC64			= 0x15,
			ELF_ISA_S390			= 0x16,
			ELF_ISA_SPU				= 0x17,
			ELF_ISA_V800			= 0x24,
			ELF_ISA_FR20			= 0x25,
			ELF_ISA_RH_32			= 0x26,
			ELF_ISA_RCE				= 0x27, //  fuck yeah
			ELF_ISA_ARM				= 0x28,
			ELF_ISA_ALPHA			= 0x29,
			ELF_ISA_SUPERH			= 0x2a,
			ELF_ISA_SPARC_VERSION_9 = 0x2b,
			ELF_ISA_TRICORE			= 0x2c,
			ELF_ISA_ARC				= 0x2d,
			ELF_ISA_HITACHI_H8_300	= 0x2e,
			ELF_ISA_HITACHI_H8_300H = 0x2f,
			ELF_ISA_HITACHI_H8S		= 0x30,
			ELF_ISA_HITACHI_H8_500	= 0x31,
			ELF_ISA_IA_64			= 0x32,
			ELF_ISA_MIPS_X			= 0x33,
			ELF_ISA_COLDFIRE		= 0x34,
			ELF_ISA_M68HC12			= 0x35,
			ELF_ISA_MMA				= 0x36, //  AND HIS NAME IS JOHN CENA
			ELF_ISA_PCP				= 0x37, //  LET'S GET FUCKED UP
			ELF_ISA_CELL			= 0x38,
			ELF_ISA_NDR1			= 0x39,
			ELF_ISA_STARCORE		= 0x3a,
			ELF_ISA_ME16			= 0x3b,
			ELF_ISA_ST100			= 0x3c,
			ELF_ISA_TINYJ			= 0x3d,
			ELF_ISA_X86_64			= 0x3e,
			ELF_ISA_DSP				= 0x3f,
			ELF_ISA_PDP_10			= 0x40,
			ELF_ISA_PDP_11			= 0x41, //  haxxx
			ELF_ISA_FX66			= 0x42,
			ELF_ISA_ST9				= 0x43,
			ELF_ISA_ST7				= 0x44,
			ELF_ISA_MC68HC16		= 0x45,
			ELF_ISA_MC68HC11		= 0x46,
			ELF_ISA_MC68HC08		= 0x47,
			ELF_ISA_MC68HC05		= 0x48,
			ELF_ISA_SVX				= 0x49,
			ELF_ISA_VAX				= 0x4b,
			ELF_ISA_AXIS_32			= 0x4c,
			ELF_ISA_INFINEON_32		= 0x4d,
			ELF_ISA_ELEMENT_14		= 0x4e,
			ELF_ISA_LSI_LOGIC		= 0x4f,
			ELF_ISA_TMS320C6000		= 0x8c,
			ELF_ISA_ELBRUS			= 0xaf,
			ELF_ISA_ARM64			= 0xb7,
			ELF_ISA_Z80				= 0xdc,
			ELF_ISA_RISC_V			= 0xf3,
			ELF_ISA_BPF				= 0xf7,
			ELF_ISA_WDC_65C816		= 0x101,
		} raw_elf_isa_t;

		typedef enum {
			ELF_SEGMENT_NULL			   = 0x0,
			ELF_SEGMENT_LOAD			   = 0x1,
			ELF_SEGMENT_DYNAMIC			   = 0x2,
			ELF_SEGMENT_INTERPRETER		   = 0x3,
			ELF_SEGMENT_NOTE			   = 0x4,
			ELF_SEGMENT_SHLIB			   = 0x5,
			ELF_SEGMENT_PROGRAM_HEADER	   = 0x6,
			ELF_SEGMENT_TLS				   = 0x7,
			ELF_SEGMENT_RESERVED_OS		   = 0x60000000,
			ELF_SEGMENT_RESERVED_PROCESSOR = 0x70000000,
		} raw_elf_segment_type_t;

		typedef struct {
				raw_elf_addr_size_t	 addr_size;
				raw_elf_endianness_t endianness;
				raw_elf_abi_t		 abi;
				uint8_t				 abi_version;
				raw_elf_obj_type_t	 obj_type;
				raw_elf_isa_t		 isa;
				uint64_t			 entry_address;
				uint64_t			 section_header_offset;
				uint32_t			 flags;
				uint16_t			 program_header_entry_size;
				uint16_t			 program_header_entry_count;
				uint16_t			 section_header_entry_size;
				uint16_t			 section_header_entry_count;
				uint16_t			 section_header_name_entry_index;
		} raw_elf_file_header_t;

		typedef struct {
				raw_elf_segment_type_t segment_type;
				uint32_t			   flags;
				uint64_t			   offset;
				uint64_t			   virtual_addr;
				uint64_t			   physical_addr;
				uint64_t			   size_in_file;
				uint64_t			   size_in_memory;
				uint64_t			   alignment;
		} raw_elf_program_header_t;

		raw_elf_file_header_t parse_elf_binary_raw(std::vector<uint8_t> buf);

		std::string to_string_raw(raw_elf_file_header_t file_header);
	} //  namespace ELF
} //  namespace XParse

#endif