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
#include <vienna/ARMv7Decompiler.hpp>
#include <libmedusa/libmedusa.hpp>
#include <libmedusa/Machine.hpp>
#include <vienna/vienna.hpp>
#include <algorithm>
#include <iterator>
#include <cstring>
#include <cstdio>
#include <vector>
#include <regex>
#include <lib.h>

using namespace vienna;

typedef struct {
	std::string regex;
	std::string replace;
} regex_replace_t;

std::vector<regex_replace_t> all_patterns_armv7; // wip
std::vector<regex_replace_t> all_shortcuts_armv7; // wip

struct cpu_definition_walker : pugi::xml_tree_walker {
	virtual bool begin(pugi::xml_node& node) {
		return true;
	}

	regex_replace_t current;

	virtual bool for_each(pugi::xml_node& node) {
		if (strcmp((char*)node.name(), "") != 0) {
			if (strcmp(node.first_child().value(), "") != 0) {
				if (strcmp(node.name(), "asm") == 0) {
//					std::regex tmp(node.first_child().value());
					current.regex = node.first_child().value();
				} else if (strcmp(node.name(), "pc") == 0) {
					current.replace = node.first_child().value();
					all_patterns_armv7.push_back(current);
				}

				if (strcmp(node.name(), "regex") == 0) {
					current.regex = node.first_child().value();
//					current.regex = tmp;
				} else if (strcmp(node.name(), "replace") == 0) {
					current.replace = node.first_child().value();
					all_shortcuts_armv7.push_back(current);
				}
			}
		}

		return true;
	}
};

std::string vienna::decompile_armv7(std::vector<uint8_t>& machine_code) {
	printf("vienna::test_function test printf\n");

	/*
	 *  create an ARMv7Machine, and a vector to hold the ARMv7 code.
	 *
	 *  then, get the vector of insn_t's from armv7_machine.disassemble(...).
	 *  pass 0 for no flags. (not THUMB)
	 */
	libmedusa::ARMv7Machine armv7_machine;
	std::vector<libmedusa::insn_t> insns;
	insns = armv7_machine.disassemble(machine_code, XP_FLAG_NOREGNAME);

	std::string ret;

	/*
	 *  loop through all instructions in the disassembly, and print out the
	 *  insn, as well as add the mnemonic and op_str to raw_asm for later IR
	 *  conversion
	 */
	printf("\n");
	printf("disassembly\n");
	printf("--------------------------------------------------------------------------------\n");

	std::string raw_asm;

	for (int i = 0; i < insns.size(); i++) {
		raw_asm += string_format("%x ", insns[i].address);
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

	printf("\n");
	printf("disassembly -> IR patterns\n");
	printf("--------------------------------------------------------------------------------\n");

	/*
	 *  load ARMv7.xml cpu definition
	 */
	pugi::xml_document doc;
	pugi::xml_parse_result result;

	result = doc.load_file("res/src/cpu_definitions/ARMv7.xml");

	if (!result) {
		return ret;
	}

	/*
	 *  `cpu_definition_walker` traverses the XML document, and once it
	 *  encounters an `asm` value it sets a temporary value to the value in the
	 *  document. when it finds a `pc` value it sets the temp val to the doc val
	 *  and pushes it to the back of the `all_patterns_armv7` vector.
	 */
	cpu_definition_walker walker;
	doc.traverse(walker);

	for (regex_replace_t& i : all_patterns_armv7) {
		std::string i_regex_replaced = i.regex;
		for (regex_replace_t& j : all_shortcuts_armv7) {
			std::regex the_regex(j.regex);
			std::string tmp;

			std::regex_replace(std::back_inserter(tmp),
							   i_regex_replaced.begin(),
							   i_regex_replaced.end(),
							   the_regex,
							   j.replace);

			i_regex_replaced = tmp;
		}

		i.regex = i_regex_replaced;
	}

	std::string asm_out = raw_asm;

	printf("%s\n", asm_out.c_str());

	fprintf(stderr, "regex\n");
	for (regex_replace_t& i : all_patterns_armv7) {
		printf("\n");
		printf("--------------------------------------------------------------------------------\n");
		std::regex the_regex(i.regex);
		printf("ASM=\"%s\" PC=\"%s\"\n", i.regex.c_str(), i.replace.c_str());
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

		printf("%s\n", asm_out.c_str());
	}

	fprintf(stderr, "str_split\n");
	std::vector<std::string> split_str = str_split(asm_out, "\n");

	std::vector<uint64_t> jumped_to;

	fprintf(stderr, "jumped_to\n");
	for (std::string& s : split_str) {
		if (s.find("__jump(") != -1) {
			std::string tmp = s.substr(s.find("__jump") + 7);
			tmp = tmp.substr(0, tmp.length() - 2);

//			printf("%s %s\n", s.c_str(), tmp.c_str());
			jumped_to.push_back(std::stoi(tmp, 0, 16));
		}
	}

	int i = 0;

	fprintf(stderr, "labels\n");
	for (std::string& s : split_str) {
//		printf("%s\n", s.substr(0, s.find(" ")).c_str());
		uint64_t addy = stoi(s.substr(0, s.find(" ")), 0, 16);
		if (std::find(jumped_to.begin(), jumped_to.end(), addy) != std::end(jumped_to)) {
			std::string tmp = string_format("__label%d:\n%s", i, s.c_str());
			s = tmp;
			i++;
		}
	}

	ret = "";

	fprintf(stderr, "regen\n");
	for (std::string& s : split_str) {
		ret += s + "\n";
	}

	printf("\n");
	printf("IR\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("%s\n", asm_out.c_str());

out:
	return ret;
}
