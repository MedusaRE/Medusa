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

#include <sys/socket.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstdio>

int main(int argc, char* argv[]) {
	struct sockaddr_un name;
	size_t size;
	int sock;

	sock = socket(PF_LOCAL, SOCK_DGRAM, 0);

	name.sun_family = AF_LOCAL;
	strncpy(name.sun_path, argv[1], sizeof(name.sun_path));

	size = ((offsetof(struct sockaddr_un, sun_path)
			+ strlen(name.sun_path)));
	
	bind(sock, (struct sockaddr*)&name, size);

	listen(sock, 1);
	int data_sock = accept(sock, NULL, NULL);

	while (1) {
		char c[1];

		read(data_sock, c, 1);

		printf("%c", c[0]);
	}

	return 0;
}