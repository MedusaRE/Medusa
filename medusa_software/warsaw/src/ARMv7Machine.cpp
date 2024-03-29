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

#include <cstring>
#include <paris/message.hpp>
#include <paris/paris.hpp>
#include <vector>
#include <warsaw/ARMv7Machine.hpp>
#include <warsaw/Machine.hpp>

//  TODO: implement the rest of (machine_op_t::*) msg op's
bool warsaw::ARMv7Machine::process_message(paris::paris_message_t message,
										   paris::Server		 *server) {
	printf("ARMv7Machine! %lx: %lu\n", message.service_id, message.uid);

	if (!message.msg_contents) {
		return false;
	}

	machine_msg msg = *(machine_msg *)message.msg_contents;

	if (msg.op == SET_REG) {
		SET_REG_args set_reg_args = *(SET_REG_args *)msg.data;
		this->armv7_machine.set_register(set_reg_args.reg);
	} else if (msg.op == GET_REGS) {
		std::vector<libmedusa::reg_t> regs = this->armv7_machine.get_registers();
		paris::paris_message_t reply_message;

		//  TODO: re-factor paris to allow free-ing parts like msg_contents

		reply_message.service_id   = message.service_by;
		reply_message.len		   = regs.size() * sizeof(libmedusa::reg_t);
		reply_message.msg_contents = (uint8_t *)calloc(regs.size(),
													   sizeof(libmedusa::reg_t));

		if (!reply_message.msg_contents) {
			return false;
		}

		memcpy((void *)reply_message.msg_contents, regs.data(), reply_message.len);

		server->send_message(reply_message);
	} else if (msg.op == READ_MEM) {
		READ_MEM_args		   args = *(READ_MEM_args *)msg.data;
		paris::paris_message_t reply_message;

		std::vector<uint8_t> vec = this->armv7_machine.read_memory(args.addr, args.size);

		reply_message.service_id   = message.service_by;
		reply_message.len		   = vec.size();
		reply_message.msg_contents = (uint8_t *)calloc(vec.size(), 1);

		memcpy((void *)reply_message.msg_contents, vec.data(), reply_message.len);

		server->send_message(reply_message);
	} else if (msg.op == WRITE_MEM) {
		WRITE_MEM_args *args = (WRITE_MEM_args *)msg.data;

		if (!args) {
			return false;
		}

		std::vector<uint8_t> vec(args->data, args->data + args->size);
		this->armv7_machine.write_memory(args->addr, vec);
	} else if (msg.op == MAP_MEM) {
		MAP_MEM_args *args = (MAP_MEM_args *)msg.data;

		if (!args) {
			return false;
		}

		this->armv7_machine.map_memory(args->mem_reg);
	} else if (msg.op == UNMAP_MEM) {
		UNMAP_MEM_args *args = (UNMAP_MEM_args *)msg.data;

		if (!args) {
			return false;
		}

		this->armv7_machine.unmap_memory(args->mem_reg);
	} else if (msg.op == EXEC_CODE_STEP) {
		printf("%s\n", this->armv7_machine.exec_code_step() ? "true" : "false");
	} else if (msg.op == EXEC_CODE_ADDR) {
		EXEC_CODE_ADDR_args *args = (EXEC_CODE_ADDR_args *)msg.data;

		if (!args) {
			return false;
		}

		printf("%s\n", this->armv7_machine.exec_code_addr(args->addr, args->size) ? "true" : "false");
	} else if (msg.op == EXEC_CODE_ADDR_NINSNS) {
		EXEC_CODE_ADDR_NINSNS_args *args = (EXEC_CODE_ADDR_NINSNS_args *)msg.data;

		if (!args) {
			return false;
		}

		// clang-format off
		printf("%s\n", this->armv7_machine.exec_code_addr_ninsns(args->addr, args->num) ? "true" : "false");
		// clang-format on
	} else if (msg.op == EXEC_CODE_NINSNS) {
		EXEC_CODE_NINSNS_args *args = (EXEC_CODE_NINSNS_args *)msg.data;

		if (!args) {
			return false;
		}

		printf("%s\n", this->armv7_machine.exec_code_ninsns(args->num_insns) ? "true" : "false");
	} else if (msg.op == GET_MEM_REGIONS) {
		std::vector<libmedusa::mem_reg_t> memory_regions = this->armv7_machine.get_memory_regions();
		paris::paris_message_t reply_message;

		reply_message.service_id   = message.service_by;
		reply_message.len		   = memory_regions.size();
		reply_message.msg_contents = (uint8_t *)calloc(memory_regions.size(),
													   sizeof(libmedusa::mem_reg_t));

		memcpy((void *)reply_message.msg_contents,
			   memory_regions.data(),
			   reply_message.len);

		server->send_message(reply_message);
	} else if (msg.op == FIND_MEMORY_REGION) {
		FIND_MEMORY_REGION_args *args = (FIND_MEMORY_REGION_args *)msg.data;
		paris::paris_message_t	 reply_message;

		if (!args) {
			return false;
		}

		libmedusa::mem_reg_t memory_region = this->armv7_machine.find_memory_region(args->addr);

		reply_message.service_id = message.service_by;
		reply_message.len		 = sizeof(memory_region);
		reply_message.msg_contents = (uint8_t *)calloc(1, sizeof(libmedusa::mem_reg_t));

		memcpy((void *)reply_message.msg_contents, &memory_region, reply_message.len);

		server->send_message(reply_message);
	}

	return true;
}

bool warsaw::ARMv7Machine::builtin_init(paris::Server *server) {
	printf("ARMv7Machine!\n");

	return true;
}