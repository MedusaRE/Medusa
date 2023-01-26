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

/*
 *  half stolen from
 * https://github.com/lief-project/LIEF/blob/master/examples/cpp/elf_reader.cpp
 */

#include <LIEF/LIEF.hpp>
#include <assert.h>
#include <iostream>
#include <memory>
#include <stdio.h>

using namespace std;

template<typename T> std::string to_string(const T& value) {
	std::ostringstream os;
	os << value;
	return os.str();
}

int main(int argc, char *argv[]) {
#if 0
	if (argc < 2) {
		fprintf(stderr, "usage: %s [path to binary]\n", argv[0]);
		exit(-1);
	}
#endif

	char *path_to_binary = (char *)"/bin/cat";

	unique_ptr<const LIEF::ELF::Binary> binary = unique_ptr<const LIEF::ELF::Binary>{
		LIEF::ELF::Parser::parse(path_to_binary)};
	binary->functions();

	//	printf("%s\n", to_string(binary->header()).c_str());

	cout << "Binary: " << binary->name() << '\n';
	cout << "Interpreter: " << binary->interpreter() << '\n';
	cout << "== Header ==" << '\n';
	cout << binary->header() << '\n';
	cout << "== Sections ==" << '\n';
	for (const LIEF::ELF::Section& section: binary->sections()) {
		cout << section << '\n';
	}

	return 0;
}