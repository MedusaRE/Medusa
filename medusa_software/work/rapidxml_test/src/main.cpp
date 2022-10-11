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
	doc.parse<0>((char*)s.c_str());


	rapidxml::xml_node<>* node = doc.first_node()->first_node();
	
	do {
		printf("%s\n", node->name());
		node = node->next_sibling();
	} while (node != NULL);


	return 0;
}