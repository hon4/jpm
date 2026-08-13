#include "show_ver_help.hpp"
#include <cstdio>

#define JPM_VERSION "0.0.1"

void show_help() {
	printf("JPM (JLinux Package Manager)\n=============================\nUsage: jpm [OPTIONS] <command> [OPTIONS]\nUsage: jpm add <package>\n\nCommands:\n  add <package>    Install a package\n\nOptions:\n  -h, --help       Show this help message and exit\n  -v, --version    Print version information and exit\n  --in-root <path> Path to install package(s) in instead of root.\n\n");
}

void show_ver() {
	printf("JPM (JLinux Package Manager)\n=============================\nVersion: %s\nCoded by: hon\nLanguage: C++\n\n",JPM_VERSION);
}
