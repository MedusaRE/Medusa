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

#include <warsaw/ARMv7Machine.hpp>
#include <warsaw/Machine.hpp>
#include <paris/message.hpp>
#include <paris/paris.hpp>
#include <vector>
#include <cstring>

// TODO: implement the rest of (machine_op_t::*) msg op's
bool warsaw::ARMv7Machine::process_message(paris::paris_message_t message,
										   paris::Server* server) {
	printf("ARMv7Machine! %lx: %lu\n", message.service_id, message.uid);

	if (!message.msg_contents) {
		return false;
	}

	machine_msg msg = *(machine_msg*)message.msg_contents;

	if (msg.op == SET_REG) {
		SET_REG_args set_reg_args = *(SET_REG_args*)msg.data;
		this->armv7_machine.set_register(set_reg_args.reg);
	} else if (msg.op == GET_REGS) {
		std::vector<libmedusa::reg_t> regs = this->armv7_machine.get_registers();
		paris::paris_message_t reply_message;

		reply_message.service_id = message.service_by;
		reply_message.len = regs.size() * sizeof(libmedusa::reg_t);
		reply_message.msg_contents = (uint8_t*)calloc(regs.size(), sizeof(libmedusa::reg_t));

		if (!reply_message.msg_contents) {
			return false;
		}

		memcpy((void*)reply_message.msg_contents, regs.data(), reply_message.len);

		server->send_message(reply_message);
	}

	return true;
}

bool warsaw::ARMv7Machine::builtin_init(paris::Server* server) {
	printf("ARMv7Machine!\n");

	return true;
}