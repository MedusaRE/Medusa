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

#include "armv7/armv7.h"
#include "armv7/state.h"
#include "macros.h"

#include <stdio.h>
#include <string.h>
#include <unicorn/unicorn.h>

#define BASE_ADDY 0x0

uint8_t test_arm_thumb_code[] = {
	0x41,
	0x20, //	movs	r0,	#0x41
	0x40,
	0xF2,
	0x20,
	0x40, //	movw	r0,	#0x420
	0x40,
	0xF2,
	0x69,
	0x01, //	movw	r1,	#0x69
	0xA0,
	0xEB,
	0x01,
	0x00, //	sub		r0,	r0,	r1
	0x01,
	0x44, //	add		r1,	r1,	r0
};

armv7_history_t history;

void hook_code(uc_engine *uc, uint64_t address, uint32_t size, void *user_data) {
	uint32_t regs[16];

	armv7_state_t current_state;

	for (int i = 0; i < len_of(armv7_regs); i++) {
		uc_reg_read(uc, armv7_regs[i], &regs[i]);
		current_state.reg_state.regs[i] = regs[i];
	}

#if 0
	printf("Register all the things!\n");
	for (int i = 0; i < len_of(armv7_regs); i++) {
		uc_reg_read(uc, armv7_regs[i], &regs[i]);
		printf("%s:\t0x%08x\n", armv7_reg_string_normal[i], regs[i]);
	}
#endif

	memcpy(&history.states[history.position], &current_state, sizeof(current_state));

	history.length++;
	history.position++;
}

int main(int argc, char *argv[]) {
	printf("Unicorn Testing...\n");
	uc_engine *uc;
	uc_hook	   hook1;
	uc_err	   err;

	history.length			   = 0;
	history.allocated_elements = DEFAULT_LENGTH;
	history.position		   = 0;
	history.states = (armv7_state_t *)calloc(history.allocated_elements,
											 sizeof(armv7_state_t));

	err = uc_open(UC_ARCH_ARM, UC_MODE_THUMB, &uc);
	if (err) {
		printf("Failed on uc_open() with error returned: %u (%s)\n", err, uc_strerror(err));
		return -1;
	}

	uc_mem_map(uc, BASE_ADDY, 0x100000, UC_PROT_ALL);
	uc_mem_write(uc, BASE_ADDY, test_arm_thumb_code, sizeof(test_arm_thumb_code));

	uc_hook_add(uc, &hook1, UC_HOOK_CODE, (void *)hook_code, NULL, BASE_ADDY, BASE_ADDY + sizeof(test_arm_thumb_code));

	err = uc_emu_start(uc, BASE_ADDY | 1, BASE_ADDY + sizeof(test_arm_thumb_code), 0, 0);
	if (err) {
		printf("Failed on uc_emu_start() with error returned: %u\n", err);
	}

	uc_close(uc);

	for (int i = 0; i < history.length; i++) {
		printf("================================\n");
		printf("armv7 state %d\n", i);
		printf("================================\n");

		printf("Registers:\n");
		for (int j = 0; j < len_of(history.states[i].reg_state.regs); j++) {
			printf("%s:\t0x%08x\n",
				   armv7_reg_string_normal[i],
				   history.states[i].reg_state.regs[j]);
		}
	}

	free(history.states);

	return 0;
}
