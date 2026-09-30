#include "show_ver_help.hpp"
#include <cstdio>
//#include "jpm_arch.hpp" //Arch is not ready

#define JPM_VERSION "0.0.2"

void show_help() {
	printf("JPM (JLinux Package Manager)\n=============================\nUsage: jpm [OPTIONS] <command> [OPTIONS]\nUsage: jpm add <package>\n\nCommands:\n  add <package>    Install a package\n\nOptions:\n  -h, --help       Show this help message and exit\n  -v, --version    Print version information and exit\n  --root <path>    Path to install package(s) in instead of root.\n  --repo <repourl> Specify the repository to use.\n\n");
}

void show_ver() {
	printf("JPM (JLinux Package Manager)\n=============================\nVersion: %s\nCoded by: hon\nLanguage: C++\n\n",JPM_VERSION);
	//Architecture is not ready.
	//printf("Arch: %s\n",JPM_ARCHITECTURE);
}
