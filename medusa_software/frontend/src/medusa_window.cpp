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

#include <capstone/capstone.h>
#include <unicorn/unicorn.h>
#include "medusa_window.h"
#include "logging.h"
#include <gtkmm.h>
#include "lib.h"

using namespace std;

#define ADDRESS_FORMAT "0x%08llx"
#define DISASSEMBLY_STR ADDRESS_FORMAT ":\t%s\t%s"

#define BASE_ADDY 0x0

size_t len;

char*   disassembly_text = NULL;
uint8_t test_arm_thumb_code[] = {
	0x41, 0x20,						//	movs	r0,	#0x41
	0x40, 0xF2, 0x20, 0x40,			//	movw	r0,	#0x420
	0x40, 0xF2, 0x69, 0x01,			//	movw	r1,	#0x69
	0xA0, 0xEB, 0x01, 0x00,			//	sub		r0,	r0,	r1
	0x01, 0x44,						//	add		r1,	r1,	r0
	0x00, 0x00,						//  mov		r0,	r0
};

uint32_t   global_pc = 0;
uc_engine *uc_global;
csh		   handle;

uc_arm_reg dump_regs[] = {
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
};

char* out_str = (char*)"";

char* format_uc(uc_engine* uc) {
	uint8_t	 instruction[4];
	uint32_t regs[16];
	uint32_t address;
	cs_insn	*insn;
	string	 str;
	char	*ret;

	uc_reg_read(uc, UC_ARM_REG_PC, &address);

	uc_mem_read(uc,
				address,
				instruction,
				4);

	cs_disasm(handle,
			  instruction,
			  4,
			  address,
			  1,
			  &insn);

	ret = (char*)"";

	for (int i = 0; i < 0x10; i++) {
		uc_reg_read(uc, dump_regs[i], &regs[i]);
	}

	str = string_format_cstr(DISASSEMBLY_STR "\n",
							 (unsigned long long)insn[0].address,
							 insn[0].mnemonic,
							 insn[0].op_str);

	str += "Registers:\n";

	for (int i = 0; i < LIST_LEN(dump_regs); i++) {
		str += string_format_cstr("r%d:\t0x%08x\n", i, regs[i]);
	}

	ret = strdup((char*)str.c_str());

	return ret;
}

void medusa_window::step_clicked() {
	uc_err err;

	medusa_log(LOG_VERBOSE, "Beginning emulation...");
	uc_reg_read(uc_global, UC_ARM_REG_R15, &global_pc);

	if (global_pc >= (BASE_ADDY + len)) {
		Gtk::MessageDialog dialog(*this,
								  "End of emulation",
								  false,
								  Gtk::MESSAGE_QUESTION,
								  Gtk::BUTTONS_OK);
		dialog.set_secondary_text("You have reached the end of the binary available for emulation.");

		int result = dialog.run();

		return;
	}

	err = uc_emu_start(uc_global, global_pc | 1, -1, 0, 1);
	if (err) {
		medusa_log(LOG_ERROR, "Failed on uc_emu_start() with error returned: %u\n",
				  err);
	}

	out_str = format_uc(uc_global);
	reg_view.get_buffer()->set_text(out_str);
}

medusa_window::medusa_window(int   argc,
						   char* argv[]) {
	string disassembly_text_str;
	char* filename = NULL;
	uc_hook hook1;
	cs_insn* insn;
	size_t count;
	uint8_t* buf;
	uc_err err;
	int i;

	Gtk::Window::set_default_icon_from_file("../../res/img/medusa_logo_lus_rounded.png");

	medusa_log(LOG_INFO, "Landed in medusa_window.");
	medusa_log(LOG_INFO, "Asking for file for disassembly...");
	Gtk::FileChooserDialog dialog("Please choose a file for disassembly.",
								  Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialog.set_transient_for(*this);

	dialog.add_button("_Cancel",	Gtk::RESPONSE_CANCEL);
	dialog.add_button("_Open",		Gtk::RESPONSE_OK);

	int result = dialog.run();
	switch (result) {
		case (Gtk::RESPONSE_OK): {
			/*
			 *  strdup because otherwise it breaks or something
			 *  god, i love memory management
			 */

			medusa_log(LOG_INFO, "User chose to open file.");
			filename = strdup(dialog.get_filename().c_str());
			medusa_log(LOG_INFO, "Filename: %s", filename);
			break;
		} case (Gtk::RESPONSE_CANCEL): {
			medusa_log(LOG_INFO, "User cancelled file opening.");
			filename = NULL;
			break;
		} default: {
			medusa_log(LOG_ERROR, "Something went wrong.");
			return;
			break;
		}
	}

	if (filename == NULL) {
		medusa_log(LOG_INFO, "Using built-in test code.");
		buf = test_arm_thumb_code;
		len = sizeof(test_arm_thumb_code);
	} else {
		medusa_log(LOG_INFO, "Opening %s...",
				  filename);
		FILE   *fp	= fopen(filename, "rb");

		fseek(fp, 0, SEEK_END);
		len	= ftell(fp);
		rewind(fp);

		medusa_log(LOG_INFO, "File is %d bytes (0x%x in hex) long.",
				  len,
				  len);

		/*
		 *  i'm aware that sizeof(uint8_t); should be 1 on any normal system,
		 *  and now that i think about it, it always should be (i think):
		 *  a uint8_t i think is defined as at least 8 bits, so even on systems
		 *  where CHAR_BIT != 8, it has to be at least 8, so sizeof(uint8_t)
		 *  should always be 1. i think. eh whatever security
		 */

		medusa_log(LOG_VERBOSE, "Allocating memory...");

		buf	= (uint8_t*)calloc(len,
							   len / sizeof(uint8_t));
		fread(buf,
			  sizeof(uint8_t),
			  len / sizeof(uint8_t),
			  fp);
		fclose(fp);
	}

	set_title(string_format_cstr("Medusa - %s",
								 (filename != NULL) ? filename
			 										: "default THUMB test code").c_str());
	set_default_size(800,
					 600);

	/*
	 *  create a TextView for the disassembly, as well as a TextBuffer for
	 *  containing the text
	 */
	medusa_log(LOG_VERBOSE, "Creating GTK TextView and TextBuffer...");
	auto* our_text_view   = new Gtk::TextView();
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
	 *  open capstone handle
	 *  CS_MODE_THUMB as this is thumb code
	 */
	medusa_log(LOG_VERBOSE, "Opening Capstone handle.");
	cs_open(CS_ARCH_ARM,
			(cs_mode)(CS_MODE_THUMB),
			&handle);

	/*
	 *  disassemble it
	 */
	medusa_log(LOG_INFO, "Disassembling code...");
	count = cs_disasm(handle,
					  buf,
					  len,
					  BASE_ADDY,
					  0,
					  &insn);


	/*
	 *  initialize with empty string, otherwise it'll start with "(null)"
	 */
	medusa_log(LOG_INFO, "Formatting disassembly...");

	disassembly_text_str = "";

	/*
	 *  format it
	 */
	if (count > 0) {
		for (i = 0; i < count; i++) {
			disassembly_text_str += string_format_cstr(DISASSEMBLY_STR "\n",
													   (unsigned long long)insn[i].address,
													   insn[i].mnemonic,
													   insn[i].op_str);
		}

		/*
		 *  no memory leaks here, sir
		 */
		cs_free(insn,
				count);
	} else {
		Gtk::MessageDialog dialog(*this,
								  "Disassembly failed / no disassembly available.",
								  false,
								  Gtk::MESSAGE_QUESTION,
								  Gtk::BUTTONS_OK);
		dialog.set_secondary_text("No disassembly was completed.");

		int result = dialog.run();

		return;
	}

	disassembly_text_str += "\n\n\n";

	disassembly_text = (char*)disassembly_text_str.c_str();

	/*
	 *  open unicorn engine
	 */
	medusa_log(LOG_VERBOSE, "Opening Unicorn Engine...");
	err = uc_open(UC_ARCH_ARM,
				  UC_MODE_THUMB,
				  &uc_global);
	if (err) {
		medusa_log(LOG_ERROR, "Failed on uc_open() with error returned: %u (%s)\n",
				  err,
				  uc_strerror(err));
		return;
	}

	medusa_log(LOG_VERBOSE, "Mapping memory for emulation...");
	uc_mem_map(uc_global, BASE_ADDY, 0x100000, UC_PROT_ALL);

	medusa_log(LOG_VERBOSE, "Copying executable for emulation...");
	uc_mem_write(uc_global, BASE_ADDY, buf, len);

//	medusa_log(LOG_VERBOSE, "Adding instruction hook for emulation...");
//	uc_hook_add(uc_global, &hook1, UC_HOOK_CODE, (void*)hook_code, NULL, BASE_ADDY, BASE_ADDY + len);

	/*
	 *  set the actual thing
	 */
	our_text_buffer->set_text(disassembly_text);

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
	step_button.set_label("step instruction");
	step_button.signal_clicked().connect(sigc::mem_fun(*this, &medusa_window::step_clicked));

	medusa_log(LOG_VERBOSE, "Initializing Register View.");
	reg_view.set_editable(false);
	reg_view.set_monospace(true);

	medusa_log(LOG_VERBOSE, "Attaching step button.");
	our_grid.attach(step_button, 0, 0);

	medusa_log(LOG_VERBOSE, "Initializing grid.");
	our_grid.set_column_homogeneous(false);
	our_grid.set_row_homogeneous(false);
	our_grid.set_margin_right(0);
	our_grid.set_margin_start(0);

	medusa_log(LOG_VERBOSE, "Packing button grid into button box.");
	button_box.pack_start(our_grid);

	medusa_log(LOG_VERBOSE, "Packing ScrolledWindow & Register View into emulation box.");
	emu_box.pack_start(sw);
	emu_box.pack_start(reg_view);

	medusa_log(LOG_VERBOSE, "Initializing button box.");
	button_box.set_spacing(10);
	button_box.set_center_widget(our_grid);

	medusa_log(LOG_VERBOSE, "Initializing emulation box.");
	emu_box.set_spacing(10);
	emu_box.set_homogeneous(true);

	medusa_log(LOG_VERBOSE, "Packing button box and emulation box into main box.");
	our_box.pack_start(button_box);
	our_box.pack_start(emu_box);

	medusa_log(LOG_VERBOSE, "Initializing main box.");
	our_box.set_homogeneous(false);
	our_box.set_border_width(10);

	medusa_log(LOG_VERBOSE, "Adding ScrolledWindow...");
	add(our_box);

	out_str = format_uc(uc_global);
	reg_view.get_buffer()->set_text(out_str);

	medusa_log(LOG_VERBOSE, "Showing...");
	show_all_children();
}

medusa_window::~medusa_window() {
	/*
	 *  good little programmers, we are
	 */
	medusa_log(LOG_VERBOSE, "Closing Capstone handle...");
	cs_close(&handle);

	medusa_log(LOG_VERBOSE, "Closing Unicorn Engine...");
	uc_close(uc_global);
}
