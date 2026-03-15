#include <stdio.h>
#include <string.h>

#define JPM_VERSION "0.0.1"

void show_help();
void show_ver();

int main(int argc, char *argv[]) {
	if (argc > 1) {
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
		}
	}
	printf("JPM\n");
	return 0;
}

void show_help() {
	printf("JPM\n====\nUsage: jpm [OPTIONS] <command> [OPTIONS]\n\nOptions:\n  -h, --help     Show this help message and exit\n  -v, --version  Print version information and exit\n\nCommands:\n  add <pkgname>    Install a package\n  del <pkgname>    Remove a package\n\n");
}

void show_ver() {
	printf("JPM VER");
}
