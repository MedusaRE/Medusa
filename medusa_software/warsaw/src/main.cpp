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

#include <cstdio>
#include <paris/message.hpp>
#include <paris/paris.hpp>
#include <unistd.h>
#include <warsaw/ARMv7Machine.hpp>
#include <warsaw/Machine.hpp>

using namespace warsaw;

class WarsawTestService: public paris::ServiceListener {
	public:
		virtual bool process_message(paris::paris_message_t msg, paris::Server *server) {
			libmedusa::reg_t *regs		= (libmedusa::reg_t *)msg.msg_contents;
			uint64_t		  reg_count = msg.len / sizeof(libmedusa::reg_t);
			if (!regs) {
				printf("regs = NULL!\n");
				return false;
			}

			for (int i = 0; i < reg_count; i++) {
				printf("%s %s %016llx %016llx\n",
					   regs[i].reg_name.c_str(),
					   regs[i].reg_description.c_str(),
					   regs[i].reg_id,
					   regs[i].reg_value);
			}
			return true;
		}
};

int main(int argc, char *argv[]) {
	paris::Server server;

	warsaw::ARMv7Machine				  armv7_machine_service;
	WarsawTestService					  wservice;
	paris::DumpMsgContentsToSTDOUTService service;

	server.start_server();

	server.add_service(armv7_machine_service);
	server.add_service(service);
	server.add_service(wservice);

	paris::paris_message_t msg;

	SET_REG_args args;
	args.reg.reg_id	   = 0;
	args.reg.reg_value = 0x41424344;

	machine_msg machine_msg_obj;
	machine_msg_obj.len	 = sizeof(SET_REG_args);
	machine_msg_obj.data = (void *)&args;
	machine_msg_obj.op	 = SET_REG;

	msg.service_id	 = armv7_machine_service.get_service_id();
	msg.uid			 = 420;
	msg.msg_contents = (uint8_t *)&machine_msg_obj;

	server.send_message(msg);

	usleep(10000);

	msg.service_by		 = wservice.get_service_id();
	machine_msg_obj.len	 = 0;
	machine_msg_obj.data = NULL;
	machine_msg_obj.op	 = GET_REGS;
	server.send_message(msg);

	usleep(10000);

	MAP_MEM_args map_mem_args;
	map_mem_args.mem_reg.addr = 0;
	map_mem_args.mem_reg.size = 0x1000;
	map_mem_args.mem_reg.prot = XP_PROT_READ | XP_PROT_WRITE | XP_PROT_EXEC;

	msg.service_by		 = service.get_service_id();
	machine_msg_obj.len	 = 0;
	machine_msg_obj.data = (void *)&map_mem_args;
	machine_msg_obj.op	 = MAP_MEM;
	server.send_message(msg);

	usleep(10000);

	READ_MEM_args mem_args;
	mem_args.addr = 0;
	mem_args.size = 16;

	msg.service_by		 = service.get_service_id();
	machine_msg_obj.len	 = 0;
	machine_msg_obj.data = (void *)&mem_args;
	machine_msg_obj.op	 = READ_MEM;
	server.send_message(msg);

	usleep(10000);

	WRITE_MEM_args *wmem_args = (WRITE_MEM_args *)calloc(1, sizeof(WRITE_MEM_args) + 2);
	wmem_args->addr				 = 0;
	wmem_args->size				 = 2;
	*(uint32_t *)wmem_args->data = 0x2041;

	printf("%016lx\n", *(uint64_t *)wmem_args->data);

	msg.service_by		 = service.get_service_id();
	machine_msg_obj.len	 = sizeof(WRITE_MEM_args) + 2;
	machine_msg_obj.data = (void *)wmem_args;
	machine_msg_obj.op	 = WRITE_MEM;
	server.send_message(msg);

	usleep(10000);

	mem_args.addr = 0;
	mem_args.size = 16;

	msg.service_by		 = service.get_service_id();
	machine_msg_obj.len	 = 0;
	machine_msg_obj.data = (void *)&mem_args;
	machine_msg_obj.op	 = READ_MEM;
	server.send_message(msg);

	usleep(10000);

	mem_args.addr = 0;
	mem_args.size = 16;

	for (int i = 0; i < 2; i++) {
		msg.service_by		= service.get_service_id();
		machine_msg_obj.len = 0;
		machine_msg_obj.op	= EXEC_CODE_STEP;
		server.send_message(msg);

		usleep(10000);

		msg.service_by		 = wservice.get_service_id();
		machine_msg_obj.len	 = 0;
		machine_msg_obj.data = NULL;
		machine_msg_obj.op	 = GET_REGS;
		server.send_message(msg);

		usleep(10000);
	}

	sleep(1);
	server.stop_server();
	sleep(1);

	return 0;
}