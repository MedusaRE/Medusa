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
	0x00, 0x00, 0xA0, 0xE1,
	0x41, 0x00, 0xB0, 0xE3,
	0x20, 0x04, 0x00, 0xE3,
	0x69, 0x10, 0x00, 0xE3,
	0x01, 0x00, 0x40, 0xE0,
	0x00, 0x10, 0x81, 0xE0,
	0x00, 0x00, 0xA0, 0xE1,
};

const char* node_types[] = {
	"null", "document", "element", "pcdata", "cdata", "comment", "pi", "declaration"
};

typedef struct {
	std::string regex;
	std::string replace;
} regex_replace_t;

std::vector<regex_replace_t> all_patterns_armv7; // wip

struct simple_walker: pugi::xml_tree_walker {
	virtual bool begin(pugi::xml_node& node) {
		return true;
	}

	regex_replace_t current;

	virtual bool for_each(pugi::xml_node& node) {
		if (strcmp((char*)node.name(), "") != 0) {
/*			for (int i = 0; i < depth(); i++) {
				printf("\t");
			}

			printf("%s: %s\n", node.name(), node.first_child().value());*/

			if (strcmp(node.first_child().value(), "") != 0) {
				if (strcmp(node.name(), "asm") == 0) {
					current.regex = node.first_child().value();
				} else if (strcmp(node.name(), "pc") == 0) {
					current.replace = node.first_child().value();
					all_patterns_armv7.push_back(current);
				}
			}
		}

//		std::cout << node_types[node.type()] << ": name='" << node.name() << "', value='" << node.value() << "'\n";

		return true;
	}
};

void vienna::test_function(void) {
	printf("vienna::test_function test printf\n");

	libmedusa::ARMv7Machine armv7_machine;
	std::vector<uint8_t> tmp_vector(test_arm_code, test_arm_code + sizeof(test_arm_code));
	std::vector<libmedusa::insn_t> insns = armv7_machine.disassemble(tmp_vector, 0);
	
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

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("res/src/cpu_definitions/ARMv7.xml");

	if (!result) {
		return;
	}

	simple_walker walker;
	doc.traverse(walker);
	std::string asm_out = raw_asm;

	for (regex_replace_t& i : all_patterns_armv7) {
		std::regex the_regex(i.regex);
		printf("%s %s\n", i.regex.c_str(), i.replace.c_str());
		std::string tmp;
		std::regex_replace(std::back_inserter(tmp),
						   asm_out.begin(),
						   asm_out.end(),
						   the_regex,
						   i.replace);
		asm_out = tmp;
	}

	printf("%s\n", asm_out.c_str());

	return;
}
