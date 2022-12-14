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

const { spawnSync } = require('child_process');
const { badgen } = require('badgen');
const fs = require('fs');

function get_output(cmd) {
	const exec_obj = spawnSync("/bin/bash", ["-c", cmd]);
	var data_ret;

	data_ret = exec_obj.stdout.toString();

	return data_ret;
}

function get_return(cmd) {
	const exec_obj = spawnSync("/bin/bash", ["-c", cmd]);

	return exec_obj.status;
}

function get_build_status() {
//	return get_return("make gitlab-runner_build");
	return get_return("make");
}

function build_color(status) {
	return (status == 0) ? "green" : "red";
}

function build_label(status) {
	return (status == 0) ? "passing" : "failing";
}

const code_exts = [
	".py",
	".c",
	".cpp",
	".cc",
	".h",
	".hh",
	".hpp",
	".sh",
	".tex",
	".js",
];

fs.writeFile("res/badges/commit_count.svg", badgen({
	label: 'commit count',
	status: get_output("git rev-list --all --count"),
	color: 'red',
	style: 'classic'
}), err => {});

fs.writeFile("res/badges/loc.svg", badgen({
	label: 'lines of code',
	status: get_output("git grep -l '' | cat | xargs cloc --exclude-ext=svg | grep SUM | awk '{ print $NF }'").replace("\n", ""),
	color: 'orange',
	style: 'classic'
}), err => {});

fs.writeFile("res/badges/license.svg", badgen({
	label: 'license',
	status: "GPLv2",
	color: 'yellow',
	style: 'classic'
}), err => {});

var build_status = get_build_status();

fs.writeFile("res/badges/build.svg", badgen({
	label:  'build',
	status: build_label(build_status),
	color:  build_color(build_status),
	style:  'classic'
}), err => {});

fs.writeFile("res/badges/commit.svg", badgen({
	label:  'last commit',
	status: get_output("git rev-parse --short HEAD"),
	color:  "blue",
	style:  'classic'
}), err => {});

fs.writeFile("res/badges/branches.svg", badgen({
	label:  'no. of branches',
	status: get_output("git branch -l | wc -l"),
	color:  "purple",
	style:  'classic'
}), err => {});
