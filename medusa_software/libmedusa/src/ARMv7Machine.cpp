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

#include <algorithm>
#include <capstone/capstone.h>
#include <cstdio>
#include <cstring>
#include <libmedusa/ARMv7Machine.hpp>
#include <libmedusa/libmedusa.hpp>
#include <unicorn/unicorn.h>

using namespace libmedusa;

/*
 *  "normal" registers, contains the registers returned by get_registers.
 */
uc_arm_reg armv7_normal_regs[] = {
	UC_ARM_REG_R0,
	UC_ARM_REG_R1,
	UC_ARM_REG_R2,
	UC_ARM_REG_R3,
	UC_ARM_REG_R4,
	UC_ARM_REG_R5,
	UC_ARM_REG_R6,
	UC_ARM_REG_R7,
	UC_ARM_REG_R8,
	UC_ARM_REG_R9,
	UC_ARM_REG_R10,
	UC_ARM_REG_R11,
	UC_ARM_REG_R12,
	UC_ARM_REG_R13,
	UC_ARM_REG_R14,
	UC_ARM_REG_R15,
	UC_ARM_REG_CPSR,
};

ARMv7Machine::ARMv7Machine() {
	uc_err err;
	reg_t  reg;

	/*
	 *  open unicorn handle as thumb, that works for ARM code as well.
	 */
	err = uc_open(UC_ARCH_ARM, UC_MODE_THUMB, &this->uc);

	reg.reg_id = -1;

	/*
	 *  create descriptions for all of the registers we intend to "publish"
	 */
	reg.reg_description = "r0";
	reg.reg_name		= "r0";
	reg.reg_id++;
	reg.reg_value = 0;

	this->registers.push_back(reg);

	reg.reg_description = "r1";
	reg.reg_name		= "r1";
	reg.reg_id++;
	reg.reg_value = 0;

	this->registers.push_back(reg);

	reg.reg_description = "r2";
	reg.reg_name		= "r2";
	reg.reg_id++;
	reg.reg_value = 0;

	this->registers.push_back(reg);

	reg.reg_description = "r3";
	reg.reg_name		= "r3";
	reg.reg_id++;
	reg.reg_value = 0;

	this->registers.push_back(reg);

	reg.reg_description = "r4";
	reg.reg_name		= "r4";
	reg.reg_id++;
	reg.reg_value = 0;

	this->registers.push_back(reg);

	reg.reg_description = "r5";
	reg.reg_name		= "r5";
	reg.reg_id++;
	reg.reg_value = 0;

	this->registers.push_back(reg);

	reg.reg_description = "r6";
	reg.reg_name		= "r6";
	reg.reg_id++;
	reg.reg_value = 0;

	this->registers.push_back(reg);

	reg.reg_description = "r7";
	reg.reg_name		= "r7";
	reg.reg_id++;
	reg.reg_value = 0;

	this->registers.push_back(reg);

	reg.reg_description = "r8";
	reg.reg_name		= "r8";
	reg.reg_id++;
	reg.reg_value = 0;

	this->registers.push_back(reg);

	reg.reg_description = "r9";
	reg.reg_name		= "r9";
	reg.reg_id++;
	reg.reg_value = 0;

	this->registers.push_back(reg);

	reg.reg_description = "r10";
	reg.reg_name		= "r10";
	reg.reg_id++;
	reg.reg_value = 0;

	this->registers.push_back(reg);

	reg.reg_description = "r11";
	reg.reg_name		= "r11";
	reg.reg_id++;
	reg.reg_value = 0;

	this->registers.push_back(reg);

	reg.reg_description = "ip";
	reg.reg_name		= "ip";
	reg.reg_id++;
	reg.reg_value = 0;

	this->registers.push_back(reg);

	reg.reg_description = "sp";
	reg.reg_name		= "sp";
	reg.reg_id++;
	reg.reg_value = 0;

	this->registers.push_back(reg);

	reg.reg_description = "lr";
	reg.reg_name		= "lr";
	reg.reg_id++;
	reg.reg_value = 0;

	this->registers.push_back(reg);

	reg.reg_description = "pc";
	reg.reg_name		= "pc";
	reg.reg_id++;
	reg.reg_value = 0;

	this->registers.push_back(reg);

	reg.reg_description = "cpsr";
	reg.reg_name		= "cpsr";
	reg.reg_id++;
	reg.reg_value = 0;

	this->registers.push_back(reg);

	/*
	 *  open capstone handles for ARM and THUMB code.
	 */
	cs_open(CS_ARCH_ARM, (cs_mode)(CS_MODE_ARM), &this->handle);

	cs_open(CS_ARCH_ARM, (cs_mode)(CS_MODE_THUMB), &this->handle_thumb);

	/*
	 *  open keystone handles for ARM and THUMB code.
	 */
	ks_open(KS_ARCH_ARM, KS_MODE_ARM, &this->ks);

	ks_open(KS_ARCH_ARM, KS_MODE_THUMB, &this->ks_thumb);
}

ARMv7Machine::~ARMv7Machine() {
	//	uc_close(this->uc);
	ks_close(this->ks);
	ks_close(this->ks_thumb);
}

std::vector<reg_t> ARMv7Machine::get_registers() {
	/*
	 *  loop from 0 to the length of armv7_normal_regs, read the register, and
	 * set the value.
	 */
	for (int i = 0; i < sizeof(armv7_normal_regs) / sizeof(armv7_normal_regs[0]); i++) {
		uint32_t val;
		uc_reg_read(this->uc, armv7_normal_regs[i], &val);
		this->registers[i].reg_value = val;
	}

	return this->registers;
}

std::vector<mem_reg_t> ARMv7Machine::get_memory_regions() {
	std::vector<mem_reg_t> regions;
	uc_mem_region		  *uc_style_memory_regions;
	uint32_t			   count;

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
		region.prot = 0;
		region.prot |= (uc_style_memory_regions[i].perms & UC_PROT_READ) ? XP_PROT_READ : 0;
		region.prot |= (uc_style_memory_regions[i].perms & UC_PROT_WRITE) ? XP_PROT_WRITE : 0;
		region.prot |= (uc_style_memory_regions[i].perms & UC_PROT_EXEC) ? XP_PROT_EXEC : 0;
		regions.push_back(region);
	}

	return regions;
}

bool ARMv7Machine::map_memory(mem_reg_t memory_region) {
	bool	 ret  = true;
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
mem_reg_t ARMv7Machine::find_memory_region(uint64_t addr) {
	mem_reg_t			   fake_reg;
	std::vector<mem_reg_t> regions;

	/*
	 *  get all of the mapped memory regions
	 */
	regions = this->get_memory_regions();

	/*
	 *  check if addr is inside the region's range
	 */
	for (mem_reg_t& i: regions) {
		uint64_t start_addr = i.addr;
		uint64_t end_addr	= i.addr + i.size;
		if (addr >= start_addr && addr < end_addr) {
			return i;
		}
	}

	fake_reg.valid = false;

	return fake_reg;
}

bool ARMv7Machine::unmap_memory(mem_reg_t memory_region) {
	bool ret = true;

	/*
	 *  unmap the memory
	 */
	ret = (uc_mem_unmap(this->uc, memory_region.addr, memory_region.size) == UC_ERR_OK)
			? true
			: false;

	return ret;
}

std::vector<uint8_t> ARMv7Machine::read_memory(uint64_t addr, uint64_t size) {
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

bool ARMv7Machine::write_memory(uint64_t addr, std::vector<uint8_t>& data) {
	uint32_t size = data.size();
	bool	 ret  = true;
	uint8_t	 buf[size];

	std::copy(data.begin(), data.end(), buf);

	ret = (uc_mem_write(this->uc, addr, buf, size) == UC_ERR_OK) ? true : false;

	return ret;
}

bool ARMv7Machine::exec_code_addr(uint64_t addr, uint64_t size) {
	bool ret = true;

	ret = (uc_emu_start(this->uc, addr, addr + size, 0, 0) == UC_ERR_OK) ? true : false;

	return ret;
}

bool ARMv7Machine::exec_code_addr_ninsns(uint64_t addr, uint64_t num) {
	bool ret = true;

	/*
	 *  0xffff....L is just the max value representable by a uint64_t,
	 *  so this'll run just until num instructions is hit. (or you just run out
	 *  of memory)
	 */
	ret = (uc_emu_start(this->uc, addr, 0xffffffffffffffffL, 0, num) == UC_ERR_OK) ? true : false;

	return ret;
}

bool ARMv7Machine::exec_code_ninsns(uint64_t num) {
	bool	 ret = true;
	uint32_t cpsr;
	uint32_t val;

	/*
	 *  read PC and CPSR
	 */
	uc_reg_read(this->uc, UC_ARM_REG_PC, &val);
	uc_reg_read(this->uc, UC_ARM_REG_CPSR, &cpsr);

	/*
	 *  1 << 5 is the bit in CPSR denoting whther currently executing in THUMB
	 *  mode. prolly should add an enum or define.
	 */
	if (cpsr & (1 << 5)) {
		val |= 1;
	}

	ret = (uc_emu_start(this->uc, val, 0xffffffffffffffffL, 0, num) == UC_ERR_OK) ? true : false;

	return ret;
}

bool ARMv7Machine::exec_code_step() {
	return this->exec_code_ninsns(1);
}

bool ARMv7Machine::set_register(reg_t reg) {
	bool ret = false;

	/*
	 *  no buffer overflows here, sir!
	 */
	if (reg.reg_id <= sizeof(armv7_normal_regs) / sizeof(armv7_normal_regs[0])) {
		ret = (uc_reg_write(this->uc, armv7_normal_regs[reg.reg_id], &reg.reg_value) == UC_ERR_OK)
				? true
				: false;
	} else {
		ret = false;
	}

	return ret;
}

std::vector<insn_t> ARMv7Machine::disassemble(std::vector<uint8_t>& data, flag_t flags) {
	uint32_t size = data.size();

	uint8_t			   *buf = (uint8_t *)calloc(size, 1);
	size_t				count;
	cs_insn			   *insns;
	insn_t				insn;
	std::vector<insn_t> ret;
	cs_err				err;

	std::copy(data.begin(), data.end(), buf);

	if (flags & XP_FLAG_NOREGNAME) {
		err = cs_option(this->handle_thumb, CS_OPT_SYNTAX, CS_OPT_SYNTAX_NOREGNAME);
		err = cs_option(this->handle, CS_OPT_SYNTAX, CS_OPT_SYNTAX_NOREGNAME);
	} else {
		err = cs_option(this->handle_thumb, CS_OPT_SYNTAX, CS_OPT_SYNTAX_DEFAULT);
		err = cs_option(this->handle, CS_OPT_SYNTAX, CS_OPT_SYNTAX_DEFAULT);
	}

	if (flags & XP_FLAG_SKIPDATA) {
		err = cs_option(this->handle_thumb, CS_OPT_SKIPDATA, CS_OPT_ON);
		err = cs_option(this->handle, CS_OPT_SKIPDATA, CS_OPT_ON);
	} else {
		err = cs_option(this->handle_thumb, CS_OPT_SKIPDATA, CS_OPT_OFF);
		err = cs_option(this->handle, CS_OPT_SKIPDATA, CS_OPT_OFF);
	}

	if (flags & XP_FLAG_THUMB) {
		count = cs_disasm(this->handle_thumb, buf, size, 0, 0, &insns);
	} else {
		count = cs_disasm(this->handle, buf, size, 0, 0, &insns);
	}

	if (!insns) {
		goto out;
	}

	if (!count) {
		goto out;
	}

	for (int i = 0; i < count; i++) {
		insn.id		 = insns[i].id;
		insn.address = insns[i].address;
		insn.size	 = insns[i].size;

		insn.bytes = (uint8_t *)calloc(insn.size, 1);
		memcpy(insn.bytes, insns[i].bytes, insn.size);
		insn.mnemonic = strdup(insns[i].mnemonic);
		insn.op_str	  = strdup(insns[i].op_str);

		ret.push_back(insn);
	}

out:
	if (insns) {
		cs_free(insns, count);
	}
	if (buf) {
		free(buf);
	}

	return ret;
}

std::vector<uint8_t> ARMv7Machine::assemble(std::string src, uint64_t addr, flag_t flags) {
	ks_err				 err_ks;
	size_t				 count;
	size_t				 size;
	uint8_t				*data;
	std::vector<uint8_t> ret;

	if (flags & XP_FLAG_THUMB) {
		ks_asm(this->ks_thumb, src.c_str(), addr, &data, &size, &count);
	} else {
		ks_asm(this->ks, src.c_str(), addr, &data, &size, &count);
	}

	if (!data) {
		goto out;
	}

	if (!size) {
		goto out;
	}

	if (!count) {
		goto out;
	}

	for (int i = 0; i < size; i++) {
		ret.push_back(data[i]);
	}

	ks_free(data);

out:
	return ret;
}