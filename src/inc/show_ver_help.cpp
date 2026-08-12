#include "show_ver_help.hpp"
#include <cstdio>

#define JPM_VERSION "0.0.1"

void show_help() {
	printf("JPM\n====\nUsage: jpm [OPTIONS] <command> [OPTIONS]\nUsage: jpm <add/del> <name>\n\nOptions:\n  -h, --help     Show this help message and exit\n  -v, --version  Print version information and exit\n\nCommands:\n  add <pkgname>    Install a package\n  del <pkgname>    Remove a package\n  list             List all the installed packages on this machine.\n  update         Temp use.\n\n");
}

void show_ver() {
	printf("JPM (JLinux Package Manager)\n=============================\nVersion: %s\nCoded by: hon\nLanguage: C\n\n",JPM_VERSION);
}