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

int connect_main(int argc, char* argv[]) {
	struct sockaddr_un addr;
	int data_socket = socket(AF_UNIX, SOCK_SEQPACKET, 0);

	memset(&addr, 0, sizeof(addr));

	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, argv[2], sizeof(addr.sun_path));

	connect(data_socket, (const struct sockaddr*)&addr, sizeof(addr));

	int n = strlen(argv[3]);
	printf("%d\n", n);
	for (int i = 0; i < n; i++) {
		write(data_socket, &argv[3][i], 1);
	}

	close(data_socket);

	return 0;
}

int main(int argc, char* argv[]) {
	struct sockaddr_un name;
	size_t size;
	int sock;

	if (strcmp(argv[1], "connect") == 0) {
		return connect_main(argc, argv);
	}

	sock = socket(PF_LOCAL, SOCK_SEQPACKET, 0);
	perror("lol");

	name.sun_family = AF_LOCAL;
	strncpy(name.sun_path, argv[1], sizeof(name.sun_path));

	size = ((offsetof(struct sockaddr_un, sun_path)
			+ strlen(name.sun_path)));
	
	bind(sock, (struct sockaddr*)&name, sizeof(name));
	perror("lol");

	listen(sock, 1);
	perror("lol");
	int data_socket = accept(sock, NULL, NULL);

	while (1) {
		char c[1];

		int n = read(data_socket, c, 1);
		if (n != 1) {
			close(data_socket);
			break;
		}

		printf("%c", c[0]);
	}

	printf("\n");

	return 0;
}