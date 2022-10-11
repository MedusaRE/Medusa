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

#include "../../../submodules/rapidxml/rapidxml.hpp"
#include <cstring>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
	printf("Hello, world!\n");

	ifstream f("../../vienna/res/src/cpu_definitions/ARMv7.xml");
	stringstream ss;

	ss << f.rdbuf();

	string s = ss.str();

	rapidxml::xml_document<> doc;
	doc.parse<0>((char*)strdup((char*)s.c_str()));


	rapidxml::xml_node<>* node = doc.first_node();
	int depth = 0;

	do {
		if (node->type() == 2) {
			for (int i = 0; i < depth + 1; i++) {
				printf("\t");
			}
			printf("%s\n", node->value());
			rapidxml::xml_node<>* parent_node = node->parent();

			do {
				parent_node = parent_node->parent();
				depth--;
			} while (parent_node->next_sibling() == NULL);

			node = parent_node->next_sibling();
			depth--;
			continue;
		}

		for (int i = 0; i < depth; i++) {
			printf("\t");
		}

		printf("%s\n", node->name());

		if (node->first_node() != NULL) {
			node = node->first_node();
			depth++;
		} else if (node->next_sibling() != NULL) {
			node = node->next_sibling();
		} else {
			node = node->parent()->next_sibling();
			depth--;
		}
	} while (node != NULL);


	return 0;
}