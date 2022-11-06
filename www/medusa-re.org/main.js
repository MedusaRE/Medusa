function main() {
	if (location.hostname === "localhost")
		return;

	if (location.protocol === "http:")
		location.protocol = "https:";
}

main();
