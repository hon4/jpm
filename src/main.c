#include <stdio.h>
#include <string.h>

#define JPM_VERSION "0.0.1"

void show_help();
void show_ver();

int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf("JPM: No command. Type -h to show help.\n");
		return 1;
	}
	
	char *command;
	char *pkg_name;
	
	int i;
	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
			show_help();
			return 0;
		}
		if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
			show_ver();
			return 0;
		}
		if (argv[i][0] != '-') { /* Not starting with "-", it's a command not an option. */
			command = argv[i];
			i++; /* Increase i by one and Get package name (the next). Only for add/del/update. Future check what command eg jpm upgrade/update dont need pkg name. */
			pkg_name = argv[i];
			printf("Cmd: %s\nPkg: %s\n",command,pkg_name);
		}
	}
	printf("JPM\n");
	return 0;
}

void show_help() {
	printf("JPM\n====\nUsage: jpm [OPTIONS] <command> [OPTIONS]\nUsage: jpm <add/del> <name>\n\nOptions:\n  -h, --help     Show this help message and exit\n  -v, --version  Print version information and exit\n\nCommands:\n  add <pkgname>    Install a package\n  del <pkgname>    Remove a package\n\n");
}

void show_ver() {
	printf("JPM (JLinux Package Manager)\n=============================\nVersion: %s\nCoded by: hon\nLanguage: C\n\n",JPM_VERSION);
}
