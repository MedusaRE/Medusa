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

#include <libmedusa/ARM64Machine.hpp>
#include <libmedusa/libmedusa.hpp>
#include <capstone/capstone.h>
#include <unicorn/unicorn.h>
#include <cstring>
#include <cstdio>

using namespace libmedusa;

/*
 *  "normal" registers, contains the registers returned by get_registers.
 */
uc_arm64_reg arm64_normal_regs[] = {
	UC_ARM64_REG_X0,
	UC_ARM64_REG_X1,
	UC_ARM64_REG_X2,
	UC_ARM64_REG_X3,
	UC_ARM64_REG_X4,
	UC_ARM64_REG_X5,
	UC_ARM64_REG_X6,
	UC_ARM64_REG_X7,
	UC_ARM64_REG_X8,
	UC_ARM64_REG_X9,
	UC_ARM64_REG_X10,
	UC_ARM64_REG_X11,
	UC_ARM64_REG_X12,
	UC_ARM64_REG_X13,
	UC_ARM64_REG_X14,
	UC_ARM64_REG_X15,
	UC_ARM64_REG_X16,
	UC_ARM64_REG_X17,
	UC_ARM64_REG_X18,
	UC_ARM64_REG_X19,
	UC_ARM64_REG_X20,
	UC_ARM64_REG_X21,
	UC_ARM64_REG_X22,
	UC_ARM64_REG_X23,
	UC_ARM64_REG_X24,
	UC_ARM64_REG_X25,
	UC_ARM64_REG_X26,
	UC_ARM64_REG_X27,
	UC_ARM64_REG_X28,
	UC_ARM64_REG_FP,
	UC_ARM64_REG_SP,
	UC_ARM64_REG_PC,
};

ARM64Machine::ARM64Machine() {
	uc_err err;
	reg_t  reg;

	/*
	 *  open unicorn handle as thumb, that works for ARM code as well.
	 */
	err = uc_open(UC_ARCH_ARM64,
				  UC_MODE_ARM,
				  &this->uc);
	/*
	 *  create descriptions for all of the registers we intend to "publish"
	 */

	reg.reg_id = -1;

	reg.reg_description = "x0";
	reg.reg_name = "x0";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "x1";
	reg.reg_name = "x1";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "x2";
	reg.reg_name = "x2";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "x3";
	reg.reg_name = "x3";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "x4";
	reg.reg_name = "x4";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "x5";
	reg.reg_name = "x5";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "x6";
	reg.reg_name = "x6";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "x7";
	reg.reg_name = "x7";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "x8";
	reg.reg_name = "x8";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "x9";
	reg.reg_name = "x9";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "x10";
	reg.reg_name = "x10";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "x11";
	reg.reg_name = "x11";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "x12";
	reg.reg_name = "x12";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "x13";
	reg.reg_name = "x13";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "x14";
	reg.reg_name = "x14";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "x15";
	reg.reg_name = "x15";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "x16";
	reg.reg_name = "x16";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "x17";
	reg.reg_name = "x17";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "x18";
	reg.reg_name = "x18";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "x19";
	reg.reg_name = "x19";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "x20";
	reg.reg_name = "x20";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "x21";
	reg.reg_name = "x21";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "x22";
	reg.reg_name = "x22";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "x23";
	reg.reg_name = "x23";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "x24";
	reg.reg_name = "x24";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "x25";
	reg.reg_name = "x25";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "x26";
	reg.reg_name = "x26";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "x27";
	reg.reg_name = "x27";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "x28";
	reg.reg_name = "x28";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "fp";
	reg.reg_name = "fp";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "sp";
	reg.reg_name = "sp";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	reg.reg_description = "pc";
	reg.reg_name = "pc";
	reg.reg_id++;
	reg.reg_value = 0;
	
	this->registers.push_back(reg);

	/*
	 *  open capstone handles for ARM64 code.
	 */
	cs_open(CS_ARCH_ARM64,
			(cs_mode)(CS_MODE_ARM),
			&this->handle);

	/*
	 *  open keystone handles for ARM64 code.
	 */
	ks_open(KS_ARCH_ARM64,
			KS_MODE_LITTLE_ENDIAN,
			&this->ks);
}

ARM64Machine::~ARM64Machine() {
	uc_close(this->uc);
	ks_close(this->ks);
}

std::vector<reg_t> ARM64Machine::get_registers() {
	/*
	 *  loop from 0 to the length of arm64_normal_regs, read the register, and set the
	 *  value.
	 */
	for (int i = 0; i < sizeof(arm64_normal_regs) / sizeof(arm64_normal_regs[0]); i++) {
		uint64_t val;
		uc_reg_read(this->uc, arm64_normal_regs[i], &val);
		this->registers[i].reg_value = val;
	}

	return this->registers;
}

std::vector<mem_reg_t> ARM64Machine::get_memory_regions() {
	std::vector<mem_reg_t>	regions;
	uc_mem_region		   *uc_style_memory_regions;
	uint32_t				count;

	/*
	 *  get memory regions from unicorn, my good lord above
	 *  thank you for this function
	 */
	uc_mem_regions(this->uc, &uc_style_memory_regions, &count);

	for (int i = 0; i < count; i++) {
		mem_reg_t region;
		region.addr = uc_style_memory_regions[i].begin;
		region.size = uc_style_memory_regions[i].end - region.addr;

		/*
		 *  technically UC_PROT shit is the same as XP_PROT shit tmk, but
		 *  just in case, y'know?
		 */
		region.prot  = 0;
		region.prot |= (uc_style_memory_regions[i].perms & UC_PROT_READ) ? XP_PROT_READ : 0;
		region.prot |= (uc_style_memory_regions[i].perms & UC_PROT_WRITE) ? XP_PROT_WRITE : 0;
		region.prot |= (uc_style_memory_regions[i].perms & UC_PROT_EXEC) ? XP_PROT_EXEC : 0;
		region.valid = true;
		regions.push_back(region);
	}

	return regions;
}

bool ARM64Machine::map_memory(mem_reg_t memory_region) {
	bool	 ret = true;
	uint32_t prot = 0;
	uc_err	 err;

	/*
	 *  convert between UC_PROT and XP_PROT, which are technically the same, but
	 *  just in case things change.
	 */
	prot |= (memory_region.prot & XP_PROT_READ) ? UC_PROT_READ : 0;
	prot |= (memory_region.prot & XP_PROT_WRITE) ? UC_PROT_WRITE : 0;
	prot |= (memory_region.prot & XP_PROT_EXEC) ? UC_PROT_EXEC : 0;

	/*
	 *  map the memory
	 */
	err = uc_mem_map(this->uc, memory_region.addr, memory_region.size, prot);

	if (err) {
		fprintf(stderr, "uc_mem_map failed: %u (%s)\n", err, uc_strerror(err));
		return false;
	}

	return ret;
}

/*
 *  unused, i believe
 */
mem_reg_t ARM64Machine::find_memory_region(uint64_t addr) {
	mem_reg_t			   fake_reg;
	std::vector<mem_reg_t> regions;

	/*
	 *  get all of the mapped memory regions
	 */
	regions = this->get_memory_regions();

	/*
	 *  check if addr is inside the region's range
	 */
	for (mem_reg_t& i : regions) {
		uint64_t start_addr = i.addr;
		uint64_t end_addr = i.addr + i.size;
		if (addr >= start_addr && addr < end_addr) {
			return i;
		}
	}

	fake_reg.valid = false;

	return fake_reg;
}

bool ARM64Machine::unmap_memory(mem_reg_t memory_region) {
	bool ret = true;

	/*
	 *  unmap the memory
	 */
	ret = (uc_mem_unmap(this->uc, memory_region.addr, memory_region.size) == UC_ERR_OK) ? true : false;

	return ret;
}

std::vector<uint8_t> ARM64Machine::read_memory(uint64_t addr, uint64_t size) {
	uint8_t				 buf[size];
	uc_err				 err;
	std::vector<uint8_t> ret;

	err = uc_mem_read(this->uc, addr, buf, size);

	if (err) {
		fprintf(stderr, "uc_mem_read failed with %u (%s)\n", err, uc_strerror(err));
	}

	for (int i = 0; i < size; i++) {
		ret.push_back(buf[i]);
	}

	return ret;
}

bool ARM64Machine::write_memory(uint64_t addr, std::vector<uint8_t> data) {
	uint32_t size = data.size();
	uint8_t	 buf[size];
	bool	 ret = true;

	std::copy(data.begin(), data.end(), buf);

	ret = (uc_mem_write(this->uc, addr, buf, size) == UC_ERR_OK) ? true : false;

	return ret;
}

bool ARM64Machine::exec_code_addr(uint64_t addr, uint64_t size) {
	bool ret = true;

	ret = (uc_emu_start(this->uc, addr, addr + size, 0, 0) == UC_ERR_OK) ? true : false;

	return ret;
}

bool ARM64Machine::exec_code_addr_ninsns(uint64_t addr, uint64_t num) {
	bool ret = true;

	/*
	 *  0xffff....L is just the max value representable by a uint64_t,
	 *  so this'll run just until num instructions is hit. (or you just run out
	 *  of memory)
	 */
	ret = (uc_emu_start(this->uc, addr, 0xffffffffffffffffL, 0, num) == UC_ERR_OK) ? true : false;

	return ret;
}

bool ARM64Machine::exec_code_ninsns(uint64_t num) {
	bool	 ret = true;
	uint64_t val;

	/*
	 *  read PC
	 */
	uc_reg_read(this->uc, UC_ARM64_REG_PC, &val);

	ret = (uc_emu_start(this->uc, val, 0xffffffffffffffffL, 0, num) == UC_ERR_OK) ? true : false;

	return ret;
}

bool ARM64Machine::exec_code_step() {
	return this->exec_code_ninsns(1);
}

bool ARM64Machine::set_register(reg_t reg) {
	bool ret = false;

	/*
	 *  no buffer overflows here, sir!
	 */
	if (reg.reg_id <= sizeof(arm64_normal_regs) / sizeof(arm64_normal_regs[0])) {
		ret = (uc_reg_write(this->uc, arm64_normal_regs[reg.reg_id], &reg.reg_value) == UC_ERR_OK) ? true : false;
	} else {
		ret = false;
	}

	return ret;
}

std::vector<insn_t> ARM64Machine::disassemble(std::vector<uint8_t> data, flag_t flags) {
	uint32_t			 size = data.size();
	uint8_t				 buf[size];
	size_t				 count;
	cs_insn				*insns;
	insn_t				 insn;
	std::vector<insn_t>	 ret;

	std::copy(data.begin(), data.end(), buf);

	count = cs_disasm(this->handle,
					  buf,
					  size,
					  0,
					  0,
					  &insns);

	for (int i = 0; i < count; i++) {
		insn.id = insns[i].id;
		insn.address = insns[i].address;
		insn.size = insns[i].size;

		memcpy(insn.bytes, insns[i].bytes, sizeof(insn.bytes));
		memcpy(insn.mnemonic, insns[i].mnemonic, sizeof(insn.mnemonic));
		memcpy(insn.op_str, insns[i].op_str, sizeof(insn.op_str));

		ret.push_back(insn);
	}

	return ret;
}

std::vector<uint8_t> ARM64Machine::assemble(std::string src, uint64_t addr, flag_t flags) {
	ks_err				  err_ks;
	size_t				  count;
	size_t				  size;
	uint8_t				 *data;
	std::vector<uint8_t>  ret;

	ks_asm(this->ks,
		   src.c_str(),
		   addr,
		   &data,
		   &size,
		   &count);

	for (int i = 0; i < size; i++) {
		ret.push_back(data[i]);
	}

	ks_free(data);

	return ret;
}