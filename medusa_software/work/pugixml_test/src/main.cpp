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

#include "../../../submodules/pugixml/src/pugixml.hpp"
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <string>

using namespace std;

const char* node_types[] = {
	"null", "document", "element", "pcdata", "cdata", "comment", "pi", "declaration"
};

struct simple_walker: pugi::xml_tree_walker {
	virtual bool for_each(pugi::xml_node& node) {
		if (strcmp((char*)node.name(), "") != 0) {
			for (int i = 0; i < depth(); i++) {
				printf("\t");
			}

			printf("%s: %s\n", node.name(), node.first_child().value());
		}

//		std::cout << node_types[node.type()] << ": name='" << node.name() << "', value='" << node.value() << "'\n";

		return true;
	}
};

int main(int argc, char* argv[]) {
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("../../vienna/res/src/cpu_definitions/ARMv7.xml");

	if (!result) {
		return -1;
	}

	simple_walker walker;
	doc.traverse(walker);

	return 0;
}