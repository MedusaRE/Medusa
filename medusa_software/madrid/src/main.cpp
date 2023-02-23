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

// clang-format off
#include "lib.h"	 		// str_split
#include "logging.h" 		// medusa_log stuff

#include <iostream>			// getline, cin
#include <paris/paris.hpp>
#include <stdio.h>			// printf
#include <string>			// string
#include <vector>			// vector

// clang-format on

using namespace std;

int main(int argc, char *argv[]) {
	vector<string> split_s;
	string		   command;
	string		   s;

	paris::Server server;
	server.start_server();

	medusa_set_log_level(LOG_VERBOSE);

	while (s != "exit") {
		getline(cin, s);

		/*
		 *  split by space, that's how the arguments are delimited
		 */
		split_s = str_split(s, ' ');

		command = split_s.at(0);
		split_s.erase(split_s.begin());

		/*
		 *  print the first argument seperately, then print the rest indented.
		 *  this is done so the output will be of the format:
		 *  input: "command arg1 arg2 arg3 arg4"
		 *  ```
		 *  command:
		 *  	arg1
		 *  	arg2
		 *  	arg3
		 *  	arg4
		 *  ```
		 */

		medusa_log(LOG_VERBOSE, "%s:\n", command.c_str());

		for (string arg: split_s) {
			medusa_log(LOG_VERBOSE, "\t%s\n", arg.c_str());
		}

		if (command == "list_services") {
			vector<paris::Service *> services = server.get_services();

			if (services.size() == 0) {
				printf("no services currently added.\n");
				continue;
			}

			printf("services:\n");

			for (paris::Service *service: services) {
				printf("\t0x%lx\n", service->get_service_id());
			}
		} else if (command == "add_service") {
			//  TODO: come back to after writing Paris API updates
		}
	}

	server.stop_server();

	return 0;
}