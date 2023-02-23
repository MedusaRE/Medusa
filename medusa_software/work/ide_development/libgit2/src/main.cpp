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
	/*
	 *  setup code
	 */
	git_repository *repo;

	git_libgit2_init();

	int error = git_repository_open(&repo, argv[1]);

	if (error < 0) {
		const git_error *e = git_error_last();
		printf("%d/%d: %s\n", error, e->klass, e->message);
		exit(error);
	}

	/*
	 *  ref lookup
	 */
	git_reference *ref = NULL;
	error = git_reference_lookup(&ref, repo, "refs/heads/master");

	const git_oid *oid = git_reference_target(ref);

	git_commit *commit = NULL;
	error = git_commit_lookup(&commit, repo, oid);

	printf("%s\n", git_commit_message(commit));

	git_tree *tree = NULL;

	error = git_commit_tree(&tree, commit);

	const git_tree_entry *entry = git_tree_entry_byname(tree, argv[2]);

	git_object *object = NULL;
	git_tree_entry_to_object(&object, repo, entry);

	git_blob *blob = NULL;

	git_blob_lookup(&blob, repo, git_object_id(object));

	const void *rawcontent = git_blob_rawcontent(blob);

	git_buf filtered_content = GIT_BUF_INIT;
	error = git_blob_filtered_content(
		&filtered_content,    /* output buffer */
		blob,                 /* blob */
		"README.md",          /* path (for attribute-based filtering) */
  		true);                /* check if binary? */

	printf("%s\n", filtered_content.ptr);

	git_buf_free(&filtered_content);

	git_repository_free(repo);
	git_libgit2_shutdown();

	return 0;
}
