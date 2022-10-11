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

#include "../../submodules/pugixml/src/pugixml.hpp"
#include <libmedusa/ARMv7Machine.hpp>
#include <libmedusa/libmedusa.hpp>
#include <libmedusa/Machine.hpp>
#include <vienna/vienna.hpp>
#include <iterator>
#include <cstring>
#include <cstdio>
#include <vector>
#include <regex>

using namespace vienna;

static uint8_t test_arm_code[] = {
	0x20, 0x04, 0x00, 0xE3,
	0x69, 0x10, 0x00, 0xE3,
	0x01, 0x00, 0x40, 0xE0,
	0x00, 0x10, 0x81, 0xE0,
	0x01, 0x01, 0x90, 0xE7,
};

typedef struct {
	std::string regex;
	std::string replace;
} regex_replace_t;

std::vector<regex_replace_t> all_patterns_armv7; // wip

struct cpu_definition_walker : pugi::xml_tree_walker {
	virtual bool begin(pugi::xml_node& node) {
		return true;
	}

	regex_replace_t current;

	virtual bool for_each(pugi::xml_node& node) {
		if (strcmp((char*)node.name(), "") != 0) {
			if (strcmp(node.first_child().value(), "") != 0) {
				if (strcmp(node.name(), "asm") == 0) {
					current.regex = node.first_child().value();
				} else if (strcmp(node.name(), "pc") == 0) {
					current.replace = node.first_child().value();
					all_patterns_armv7.push_back(current);
				}
			}
		}

		return true;
	}
};

void vienna::test_function(void) {
	printf("vienna::test_function test printf\n");

	/*
	 *  create an ARMv7Machine, and a vector to hold the ARMv7 code.
	 *
	 *  then, get the vector of insn_t's from armv7_machine.disassemble(...).
	 *  pass 0 for no flags. (not THUMB)
	 */
	libmedusa::ARMv7Machine armv7_machine;
	std::vector<uint8_t> tmp_vector(test_arm_code,
									test_arm_code + sizeof(test_arm_code));
	std::vector<libmedusa::insn_t> insns;
	insns = armv7_machine.disassemble(tmp_vector, 0);

	/*
	 *  loop through all instructions in the disassembly, and print out the
	 *  insn, as well as add the mnemonic and op_str to raw_asm for later IR
	 *  conversion
	 */
	printf("--------------------------------------------------------------------------------\n");

	std::string raw_asm;

	for (int i = 0; i < insns.size(); i++) {
		raw_asm += insns[i].mnemonic;
		raw_asm += " ";
		raw_asm += insns[i].op_str;
		raw_asm += "\n";
		printf("0x%016lx (%d): %s %s\n",
			   insns[i].address,
			   insns[i].size,
			   insns[i].mnemonic,
			   insns[i].op_str);
	}

	printf("--------------------------------------------------------------------------------\n");

	/*
	 *  load ARMv7.xml cpu definition
	 */
	pugi::xml_document doc;
	pugi::xml_parse_result result;

	result = doc.load_file("res/src/cpu_definitions/ARMv7.xml");

	if (!result) {
		return;
	}

	/*
	 *  `cpu_definition_walker` traverses the XML document, and once it
	 *  encounters an `asm` value it sets a temporary value to the value in the
	 *  document. when it finds a `pc` value it sets the temp val to the doc val
	 *  and pushes it to the back of the `all_patterns_armv7` vector.
	 */
	cpu_definition_walker walker;
	doc.traverse(walker);
	std::string asm_out = raw_asm;

	for (regex_replace_t& i : all_patterns_armv7) {
		std::regex the_regex(i.regex);
		printf("%s %s\n", i.regex.c_str(), i.replace.c_str());
		std::string tmp;

		/*
		 *  use the regex_replace format for each pattern to convert as much
		 *  as possible to IR
		 */
		std::regex_replace(std::back_inserter(tmp),
						   asm_out.begin(),
						   asm_out.end(),
						   the_regex,
						   i.replace);
		asm_out = tmp;
	}

	printf("--------------------------------------------------------------------------------\n");

	printf("%s\n", asm_out.c_str());

	return;
}
