#include <iostream>
#include "inc/show_ver_help.hpp"
#include "inc/jpm_add_pkg.hpp"

int main(int argc, char* argv[]) {
	if (argc == 1) {
		printf("JPM: No command. Type -h to show help.\n");
		return 1;
	}

	for (int i = 1; i < argc; ++i) {
		std::string argx = argv[i];
		
		if (argx == "-h") {
			show_help();
			return 0;
		}
		
		if (argx == "-v") {
			show_ver();
			return 0;
		}
	}

	// Add JPM package
	if (argc == 3 && std::string(argv[1]) == "add") {
		return jpm_add_pkg(argv[2]);
	}

	return 0;
}
