const { spawnSync } = require('node:child_process');
const { badgen } = require('badgen');
const fs = require('fs');

function get_output(cmd) {
	const exec_obj = spawnSync("/bin/bash", ["-c", cmd]);
	var data_ret;

	data_ret = exec_obj.stdout.toString();

	return data_ret;
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

fs.writeFile("res/commit_count.svg", badgen({
	label: 'commit count',
	status: get_output("git rev-list --all --count"),
	color: 'red',
	style: 'classic'
}), err => {});

fs.writeFile("res/loc.svg", badgen({
	label: 'lines of code',
	status: get_output("cloc --exclude-dir=submodules,doxygen_out,.git --exclude-ext=svg . | grep SUM | awk '{ print $NF }'"),
	color: 'orange',
	style: 'classic'
}), err => {});