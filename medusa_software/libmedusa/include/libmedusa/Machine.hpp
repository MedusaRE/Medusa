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

#ifndef MACHINE_HPP
#define MACHINE_HPP

#include <cstdint>
#include <vector>
#include <string>

#define XP_PROT_READ (1 << 0)
#define XP_PROT_WRITE (1 << 1)
#define XP_PROT_EXEC (1 << 2)
#define MNEMONIC_SIZE 32

#define XP_FLAG_THUMB (1 << 0)

#define step_instruction exec_code_step

namespace libmedusa {

	/**
	 *  @brief A structure representing a CPU register.
	 */
	typedef struct {
		std::string reg_name;			/**< The name of the register. */
		std::string reg_description;	/**< A short description of the register. */
		uint64_t reg_id;				/**< The ID of the register. (unique) */
		uint64_t reg_value;				/**< The value of the register. */
	} reg_t;

	typedef uint64_t mem_prot_t;

	/**
	 *  @brief A structure representing a memory region.
	 */
	typedef struct {
		uint64_t addr;		/**< The address of the beginning of the memory region. */
		uint64_t size;		/**< The size of the memory region. */
		mem_prot_t prot;	/**< The protections of this region. */
		bool valid;			/**< True if valid region, false if invalid. */
	} mem_reg_t;

	/**
	 *  @brief A structure representing a CPU instruction.
	 */
	typedef struct {
		uint32_t id;					/**< The ID of this instruction mnemonic. (will work on in future, capstone stuff) */
		uint64_t address;				/**< The address of this instruction in memory. */
		uint16_t size;					/**< The size of this instructiony. */
		uint8_t bytes[64];				/**< The bytes, i.e. machine-code of this instruction. */
		char mnemonic[MNEMONIC_SIZE];	/**< The instruction mnemonic. (say, `"mov"`) */
		char op_str[160];				/**< The operation string. (say, `"r1, r0"`) */
	} insn_t;

	typedef uint32_t flag_t;

	/**
	 *  @brief An abstract class representing a virtual or real-silicon machine.
	 */
	class Machine {
		public:
			/**
			 *  @brief Obtain the value of all registers in this machine. 
			 * 
			 *  @return	std::vector<reg_t> An `std::vector` of all of the registers.
			 */
			virtual std::vector<reg_t> get_registers() = 0;

			/**
			 *  @brief Obtain all of the mapped memory regions in this machine.
			 * 
			 *  @return	std::vector<mem_reg_t> An `std::vector` of all of the memory regions.
			 */

			virtual std::vector<mem_reg_t> get_memory_regions() = 0;

			/**
			 *  @brief Map a region into memory. 
			 *  
			 *  @param memory_region The memory region to be mapped.
			 * 
			 *  @return	true  success
			 *  @return	false fail
			 */
			virtual bool map_memory(mem_reg_t memory_region) = 0;

			/**
			 *  @brief Unmap a region of memory.
			 *  
			 *  @param memory_region The region to unmap.
			 * 
			 *  @return	true  success
			 *  @return	false fail
			 */
			virtual bool unmap_memory(mem_reg_t memory_region) = 0;

			/**
			 *  @brief Find the memory region an address belongs to.
			 *  
			 *  @param addr	The address to find the region of.
			 * 
			 *  @return	mem_reg_t An object describing the region this address belongs to.
			 */
			virtual mem_reg_t find_memory_region(uint64_t addr) = 0;

			/**
			 *  @brief Write data into the memory of this machine.
			 *  
			 *  @param addr	The memory address to write data to.
			 *  @param data	The data to write into memory.
			 * 
			 *  @return	true  success
			 *  @return	false fail
			 */
			virtual bool write_memory(uint64_t addr, std::vector<uint8_t> data) = 0;

			/**
			 *  @brief Read data from the memory of this machine.
			 *
			 *  @param addr	The memory address to read data from.
			 *  @param size	The amount of memory to read.
			 * 
			 *  @return	std::vector<uint8_t> The data that was read from memory.
			 */
			virtual std::vector<uint8_t> read_memory(uint64_t addr, uint64_t size) = 0;

			/**
			 *  @brief Execute code in memory of a specified size at a specified address.
			 *  
			 *  @param addr	The address to execute code from/at.
			 *  @param size	The size of the block of memory to execute.
			 * 
			 *  @return	true  success
			 *  @return	false fail
			 */
			virtual bool exec_code_addr(uint64_t addr, uint64_t size) = 0;

			/**
			 *  @brief Execute code in memory of a specifed number of instructions at a specified address.
			 *  
			 *  @param addr	The address to execute code from/at.
			 *  @param num	The number of instructions to execute.
			 * 
			 *  @return	true  success
			 *  @return	false fail
			 */
			virtual bool exec_code_addr_ninsns(uint64_t addr, uint64_t num) = 0;

			/**
			 *  @brief Step forward one instruction.
			 *  
			 *  @return	true  success
			 *  @return	false fail
			 */
			virtual bool exec_code_step() = 0;

			/**
			 *  @brief Set a register value.
			 *  
			 *  @param reg The reg_t of the register & its value to set.
			 * 
			 *  @return	true  success
			 *  @return	false fail
			 */
			virtual bool set_register(reg_t reg) = 0;

			/**
			 *  @brief Execute a number of instructions at the current PC/IP/whatever it's called for this particular machine.
			 *  
			 *  @param num The number of instructions to execute.
			 * 
			 *  @return	true  success
			 *  @return	false fail
			 */
			virtual bool exec_code_ninsns(uint64_t num) = 0;

			/**
			 *  @brief Disassemble machine-code into an `std::vector` of insn_t's.
			 *  
			 *  @param data	 The machine code to disassemble.
			 *  @param flags Machine-specific flags that can modify the disassembly. 
			 * 
			 *  @return	std::vector<insn_t> The disassembled machine-code in the form of an `std::vector` of insn_t's.
			 */
			virtual std::vector<insn_t> disassemble(std::vector<uint8_t> data, flag_t flags) = 0;

			/**
			 *  @brief Assemble an `std::string` with assembly code into machine-code.
			 *  
			 *  @param src	 The source code to assemble.
			 *  @param addr	 The address at which this code would be located.
			 *  @param flags Machine-specific flags that can modify the machine-code.
			 * 
			 *  @return	std::vector<uint8_t> The assembled machine-code in the form of an `std::vector` of `uint8_t`'s.
			 */
			virtual std::vector<uint8_t> assemble(std::string src, uint64_t addr, flag_t flags) = 0;
//			virtual bool step_back() = 0;
//			virtual bool step_forward() = 0;
//			virtual bool step_instruction() = 0;
//			virtual bool run_instructions(uint64_t addr, uint64_t count) = 0;
	};
}

#endif