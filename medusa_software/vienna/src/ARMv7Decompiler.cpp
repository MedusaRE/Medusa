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
#include <jpcre2.hpp>
#include <algorithm>
#include <iterator>
#include <cstring>
#include <chrono>
#include <cstdio>
#include <vector>
#include <regex>
#include <lib.h>
#include <set>

using namespace vienna;
typedef jpcre2::select<char> jp;

typedef struct {
	std::string regex;
	std::string replace;
} regex_replace_t;

typedef struct {
	uint64_t addy;
	std::string ir;
} wip_ir_t;

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

std::string regex_replace_proper(regex_replace_t& rr, std::string& what) {
	jp::Regex re(rr.regex, "S");
	jp::RegexReplace jrr(&re);
	jrr.setSubject(what);
	jrr.setReplaceWith(rr.replace);
	jrr.setPcre2Option(PCRE2_SUBSTITUTE_GLOBAL);
	return jrr.replace();
}

std::string vienna::decompile_armv7(std::vector<uint8_t>& machine_code) {
	/*
	 *  don't optimize out the function in tests
	 */
	__asm__ __volatile__ ("");

	auto start = std::chrono::high_resolution_clock::now();
	printf("vienna::test_function test printf\n");

	all_patterns_armv7.clear();
	all_shortcuts_armv7.clear();

	/*
	 *  create an ARMv7Machine, and a vector to hold the ARMv7 code.
	 *
	 *  then, get the vector of insn_t's from armv7_machine.disassemble(...).
	 *  pass 0 for no flags. (not THUMB)
	 */
	DEBUG_INFO();
	libmedusa::ARMv7Machine armv7_machine;
	std::vector<libmedusa::insn_t> insns;
	insns = armv7_machine.disassemble(machine_code, XP_FLAG_NOREGNAME);
	DEBUG_INFO();

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

	//DEBUG_INFO();
	for (int i = 0; i < insns.size(); i++) {
		raw_asm += string_format("%x ", insns[i].address);
		raw_asm += insns[i].mnemonic;
		raw_asm += " ";
		raw_asm += insns[i].op_str;
		raw_asm += "\n";
//		printf("0x%016lx (%d): %s %s\n",
//			   insns[i].address,
//			   insns[i].size,
//			   insns[i].mnemonic,
//			   insns[i].op_str);
	}

	printf("\n");
	printf("disassembly -> IR patterns\n");
	printf("--------------------------------------------------------------------------------\n");

	/*
	 *  load ARMv7.xml cpu definition
	 */
	pugi::xml_document doc;
	pugi::xml_parse_result result;

	//DEBUG_INFO();
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

	//DEBUG_INFO();
	for (regex_replace_t& i : all_patterns_armv7) {
		std::string i_regex_replaced = i.regex;
		for (regex_replace_t& j : all_shortcuts_armv7) {
			i_regex_replaced = regex_replace_proper(j, i_regex_replaced);
		}

		i.regex = i_regex_replaced;
	}

	std::string asm_out = raw_asm;

//	printf("%s\n", asm_out.c_str());

	//DEBUG_INFO();
	fprintf(stderr, "regex %f\n", DEBUG_TIME_FLOAT);
	for (regex_replace_t& i : all_patterns_armv7) {
		printf("\n");
		printf("--------------------------------------------------------------------------------\n");
		printf("ASM=\"%s\" PC=\"%s\"\n", i.regex.c_str(), i.replace.c_str());

		/*
		 *  use the regex_replace format for each pattern to convert as much
		 *  as possible to IR
		 */
		asm_out = regex_replace_proper(i, asm_out);

//		printf("%s\n", asm_out.c_str());
	}

	//DEBUG_INFO();
	fprintf(stderr, "str_split %f\n", DEBUG_TIME_FLOAT);
	std::vector<std::string> split_str = str_split(asm_out, '\n');

	std::vector<uint64_t> jumped_to;

	//DEBUG_INFO();
	fprintf(stderr, "jumped_to %f\n", DEBUG_TIME_FLOAT);
	for (std::string& s : split_str) {
		if (s.find("__jump(") != -1) {
			std::string tmp = s.substr(s.find("__jump") + 7);
			tmp = tmp.substr(0, tmp.length() - 2);

//			printf("%s %s\n", s.c_str(), tmp.c_str());
			jumped_to.push_back(std::stoi(tmp, 0, 16));
		}
	}

	std::sort(jumped_to.begin(), jumped_to.end());

	int i = 0;

	//DEBUG_INFO();
	fprintf(stderr, "labels %f\n", DEBUG_TIME_FLOAT);
	for (std::string& s : split_str) {
//		printf("%s\n", s.substr(0, s.find(" ")).c_str());
		uint64_t addy = stoi(s.substr(0, s.find(" ")), 0, 16);
		if (std::binary_search(jumped_to.begin(), jumped_to.end(), addy)) {
			std::string tmp = string_format("__label%d:\n%s", i, s.c_str());
			s = tmp;
			i++;
		}
	}

	ret = "";

	//DEBUG_INFO();
	fprintf(stderr, "regen %f\n", DEBUG_TIME_FLOAT);
	for (std::string& s : split_str) {
		ret += s + "\n";
	}

	libmedusa::destroy_insn_t_vector(insns);

	jumped_to = std::vector<uint64_t>();
	split_str = std::vector<std::string>();
	insns = std::vector<libmedusa::insn_t>();

	printf("\n");
	printf("IR\n");
	printf("--------------------------------------------------------------------------------\n");
//	printf("%s\n", asm_out.c_str());

	//DEBUG_INFO();

out:
	return ret;
}
