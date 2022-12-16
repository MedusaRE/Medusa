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
#include <unistd.h>
#include <cstdio>

using namespace warsaw;

int main(int argc, char* argv[]) {
	paris::Server server;

	warsaw::ARMv7Machine armv7_machine_service;
	paris::DumpMsgContentsToSTDOUTService service;

	server.start_server();

	server.add_service(armv7_machine_service);
	server.add_service(service);

	paris::paris_message_t msg;

	SET_REG_args args;
	args.reg.reg_id = 0;
	args.reg.reg_value = 0x41424344;

	machine_msg machine_msg_obj;
	machine_msg_obj.len = sizeof(SET_REG_args);
	machine_msg_obj.data = (void*)&args;
	machine_msg_obj.op = SET_REG;

	msg.service_id = armv7_machine_service.get_service_id();
	msg.uid = 420;
	msg.msg_contents = (uint8_t*)&machine_msg_obj;

	server.send_message(msg);

	usleep(10000);

	msg.service_by = service.get_service_id();
	machine_msg_obj.len = 0;
	machine_msg_obj.data = NULL;
	machine_msg_obj.op = GET_REGS;
	server.send_message(msg);

	sleep(1);
	server.stop_server();
	sleep(1);

	return 0;
}