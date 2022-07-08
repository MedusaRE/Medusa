/*
 *  Copyright (C) 2022, w212 research. <contact@w212research.com>
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

#ifndef ARMV7MACHINE_HPP
#define ARMV7MACHINE_HPP

#include "libmedusa.hpp"
#include "Machine.hpp"
#include <vector>

namespace libmedusa {
	/**
	 *  @brief An Implementation of the Machine class for ARMv7.
	 */
	class ARMv7Machine : public Machine {
		public:
			/**
			 *  @brief The destructor for this Machine.
			 */
			~ARMv7Machine();

			/**
			 *  @brief The constructor for this Machine.
			 */
			ARMv7Machine();
			
			std::vector<reg_t> get_registers();
			bool set_register(reg_t reg);

			std::vector<uint8_t> read_memory(uint64_t addr, uint64_t size);
			bool write_memory(uint64_t addr, std::vector<uint8_t> data);
			std::vector<mem_reg_t> get_memory_regions();
			int find_memory_region(uint64_t addr);
			bool unmap_memory(mem_reg_t);
			bool map_memory(mem_reg_t);

			bool exec_code_addr_ninsns(uint64_t addr, uint64_t num);
			bool exec_code_addr(uint64_t addr, uint64_t size);
			bool exec_code_ninsns(uint64_t num);
			bool exec_code_step();

			std::vector<uint8_t> assemble(std::string src, uint64_t addr, flag_t flags);
			std::vector<insn_t> disassemble(std::vector<uint8_t> data, flag_t flags);
		protected:
			/**
			 *  @brief An `std::vector` of all of the memory regions mapped for this Machine.
			 */
			std::vector<mem_reg_t>	memory_regions;

			/**
			 *  @brief The Capstone handle for THUMB disassembly.
			 */
			csh						handle_thumb;

			/**
			 *  @brief An `std::vector` of all ARMv7 CPU registers.
			 */
			std::vector<reg_t>		registers;

			/**
			 *  @brief The Keystone handle for THUMB assembly.
			 */
			ks_engine			   *ks_thumb;

			/**
			 *  @brief The Capstone handle for disassembly.
			 */
			csh						handle;

			/**
			 *  @brief The Unicorn Engine for ARMv7 emulation.
			 */
			uc_engine			   *uc;

			/**
			 *  @brief The Keystone handle for assembly.
			 */
			ks_engine			   *ks;
	};
}

#endif