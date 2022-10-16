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

#include <libmedusa/libmedusa.hpp>
#include <libmedusa/Machine.hpp>
#include <capstone/capstone.h>
#include <unicorn/unicorn.h>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace libmedusa;

bool libmedusa::destroy_insn_t(libmedusa::insn_t insn) {
	bool ret = true;

	if (insn.bytes) {
		free(insn.bytes);
	}

	if (insn.mnemonic) {
		free(insn.mnemonic);
	}

	if (insn.op_str) {
		free(insn.op_str);
	}

	return ret;
}

bool libmedusa::destroy_insn_t_vector(std::vector<libmedusa::insn_t> insns) {
	bool ret = true;
	size_t size = insns.size();

	for (int i = 0; i < size; i++) {
		destroy_insn_t(insns.at(i));
	}

	return ret;
}