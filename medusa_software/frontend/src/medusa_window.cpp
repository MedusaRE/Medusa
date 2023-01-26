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

/*
 *	TODO:
 *		  * once [warsaw](/medusa_software/warsaw) has been worked on more,
 *			integrate warsaw services into frontend.
 *		  * work on integrating IDE features from
 *			[london](/medusa_software/london) into
 *			[frontend](/medusa_software/frontend)
 */

#include "medusa_window.h"

#include "lib.h"
#include "logging.h"

#include <capstone/capstone.h>
#include <chrono>
#include <cstring>
#include <gtkmm.h>
#include <paris/paris.hpp>
#include <thread>
#include <unicorn/unicorn.h>
#include <warsaw/ARMv7Machine.hpp>
#include <warsaw/Machine.hpp>

using namespace std;

bool TextTestService::process_message(paris::paris_message_t message, paris::Server *server) {
	libmedusa::reg_t *regs		= (libmedusa::reg_t *)message.msg_contents;
	uint64_t		  reg_count = message.len / sizeof(libmedusa::reg_t);
	if (!regs) {
		printf("regs = NULL!\n");
		return false;
	}

	std::string tmp;

	for (int i = 0; i < reg_count; i++) {
		tmp += string_format("%s %s %016llx %016llx\n",
							 regs[i].reg_name.c_str(),
							 regs[i].reg_description.c_str(),
							 regs[i].reg_id,
							 regs[i].reg_value);
	}

	/*
	 *	TODO: use something that isn't deprecated!
	 *
	 *	gdk_threads_enter(void); & gdk_threads_leave(void); are deprecated.
	 */
	gdk_threads_enter();
	this->our_text_buffer->set_text(tmp);
	gdk_threads_leave();

	printf("%s\n", tmp.c_str());

	//	free(message.msg_contents);

	return true;
}

void service_thread(paris::Server& server, uint64_t service_id) {
	sleep(5);
	paris::paris_message_t msg;

	msg.service_id	 = service_id;
	msg.msg_contents = (uint8_t *)"Hello, world!";
	msg.len			 = strlen((const char *)msg.msg_contents);

	server.send_message(msg);

	sleep(5);

	msg.msg_contents = (uint8_t *)"Hello, world! part 2";
	msg.len			 = strlen((const char *)msg.msg_contents);

	server.send_message(msg);

	sleep(5);
}

int n = 0;

void medusa_window::on_clicked() {
	paris::paris_message_t msg;
	auto				   start = std::chrono::high_resolution_clock::now();

#if 0
	msg.service_id = this->service.get_service_id();
	msg.msg_contents = (uint8_t*)strdup(string_format("Click event over Paris messages #%d.", n).c_str());
	msg.len = strlen((const char *)msg.msg_contents);

	this->server.send_message(msg);
#endif
	warsaw::machine_msg machine_msg_obj;

	msg.service_id	 = this->armv7_machine.get_service_id();
	msg.msg_contents = (uint8_t *)&machine_msg_obj;
	msg.service_by	 = service.get_service_id();

	machine_msg_obj.len = 0;
	machine_msg_obj.op	= warsaw::EXEC_CODE_STEP;
	server.send_message(msg);

	usleep(10000);

	machine_msg_obj.len = 0;
	machine_msg_obj.op	= warsaw::GET_REGS;
	server.send_message(msg);

	auto end = std::chrono::high_resolution_clock::now();

	printf("%.9f\n", (duration_cast<std::chrono::nanoseconds>(end - start).count()) / 1000000000.0);
}

medusa_window::medusa_window() {
	Gtk::Window::set_default_icon_from_file("/usr/share/icons/medusa.png");
	Gtk::Window::set_title("Medusa");

	medusa_log(LOG_INFO, "Landed in medusa_window.");

	set_default_size(800, 600);

	/*
	 *  create a TextView for the disassembly, as well as a TextBuffer for
	 *  containing the text
	 */
	medusa_log(LOG_VERBOSE, "Creating GTK TextView and TextBuffer...");
	auto *our_text_view	  = new Gtk::TextView();
	auto  our_text_buffer = Gtk::TextBuffer::create();

	/*
	 *  monospace looks better :P
	 *  also we don't want it to be editable
	 */
	medusa_log(LOG_VERBOSE, "Setting TextView properties...");
	our_text_view->set_monospace(true);
	our_text_view->set_editable(false);
	our_text_view->set_buffer(our_text_buffer);

	/*
	 *  set the actual thing
	 */
	our_text_buffer->set_text("Example text.");

	/*
	 *  add text view to scrolledwindow and init scrolledwindow
	 */
	medusa_log(LOG_VERBOSE, "Initializing ScrolledWindow.");

	sw.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_ALWAYS);
	sw.set_propagate_natural_width(true);

	medusa_log(LOG_VERBOSE, "Adding TextView.");
	sw.add(*our_text_view);
	sw.show_all_children();

	medusa_log(LOG_VERBOSE, "Initializing step button.");
	paris_test_button.set_label("Paris Test Button #1");

#if 0
	medusa_log(LOG_VERBOSE, "Initializing Register View.");
	reg_view.set_editable(false);
	reg_view.set_monospace(true);
#endif

	medusa_log(LOG_VERBOSE, "Attaching paris test button.");
	our_grid.attach(paris_test_button, 0, 0);

	paris_test_button.signal_clicked().connect(sigc::mem_fun(*this, &medusa_window::on_clicked));

	medusa_log(LOG_VERBOSE, "Initializing grid.");
	our_grid.set_column_homogeneous(false);
	our_grid.set_row_homogeneous(false);
	our_grid.set_margin_right(0);
	our_grid.set_margin_start(0);

#if 0
	medusa_log(LOG_VERBOSE, "Packing button grid into button box.");
	button_box.pack_start(our_grid);

//#if 0
	medusa_log(LOG_VERBOSE, "Packing ScrolledWindow & Register View into emulation box.");
	emu_box.pack_start(sw);
	emu_box.pack_start(reg_view);
//#endif

	medusa_log(LOG_VERBOSE, "Initializing button box.");
	button_box.set_spacing(10);
	button_box.set_center_widget(our_grid);

//#if 0
	medusa_log(LOG_VERBOSE, "Initializing emulation box.");
	emu_box.set_spacing(10);
	emu_box.set_homogeneous(true);
#endif

	medusa_log(LOG_VERBOSE, "Packing button box and emulation box into main box.");
	our_box.pack_start(our_grid, false, false);
	our_box.pack_start(sw, true, true);

	our_box.set_center_widget(sw);

	medusa_log(LOG_VERBOSE, "Initializing main box.");
	our_box.set_homogeneous(false);
	our_box.set_border_width(10);

	medusa_log(LOG_VERBOSE, "Adding ScrolledWindow...");
	add(our_box);

	medusa_log(LOG_VERBOSE, "Showing...");
	show_all_children();

	server.start_server();

	this->service.our_text_buffer = our_text_buffer;

	server.add_service(this->service);
	server.add_service(this->armv7_machine);

	paris::paris_message_t msg;
	warsaw::machine_msg	   machine_msg_obj;

	msg.service_id	 = this->armv7_machine.get_service_id();
	msg.msg_contents = (uint8_t *)&machine_msg_obj;
	msg.service_by	 = service.get_service_id();

	warsaw::MAP_MEM_args map_mem_args;
	map_mem_args.mem_reg.addr = 0;
	map_mem_args.mem_reg.size = 0x1000;
	map_mem_args.mem_reg.prot = XP_PROT_READ | XP_PROT_WRITE | XP_PROT_EXEC;

	machine_msg_obj.len	 = sizeof(map_mem_args);
	machine_msg_obj.op	 = warsaw::MAP_MEM;
	machine_msg_obj.data = (void *)&map_mem_args;
	server.send_message(msg);

	usleep(10000);

	warsaw::SET_REG_args set_reg_args;
	set_reg_args.reg.reg_id	   = 0xf;
	set_reg_args.reg.reg_value = 0x0;

	machine_msg_obj.len	 = sizeof(set_reg_args);
	machine_msg_obj.op	 = warsaw::SET_REG;
	machine_msg_obj.data = (void *)&set_reg_args;
	//	server.send_message(msg);

#if 0
	std::thread our_thread(service_thread,
						   std::ref(server),
						   this->service.get_service_id());

	our_thread.detach();
#endif
}

medusa_window::~medusa_window() {
	return;
}
