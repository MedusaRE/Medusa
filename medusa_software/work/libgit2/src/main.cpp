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

#include <git2/refs.h>
#include <git2.h>
#include <cstdio>

int main(int argc, char* argv[]) {
	git_repository *repo;

	git_libgit2_init();

	int error = git_repository_open(&repo, argv[1]);

	if (error < 0) {
		const git_error *e = git_error_last();
		printf("%d/%d: %s\n", error, e->klass, e->message);
		exit(error);
	}

	git_reference *ref = NULL;
	error = git_reference_lookup(&ref, repo, "refs/heads/master");

	printf("%s\n", git_reference_name(ref));

	git_repository_free(repo);
	git_libgit2_shutdown();

	return 0;
}