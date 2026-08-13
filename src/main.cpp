#include <iostream>
#include "inc/show_ver_help.hpp"
#include "inc/jpm_add_pkg.hpp"
#include "inc/global_vars.hpp"

int main(int argc, char* argv[]) {
	if (argc == 1) {
		printf("JPM: No command. Type -h to show help.\n");
		return 1;
	}
	
	std::string command; //Command like: add...
	std::string pkgs; //The pkg(s) str like "pkg1 pkg2"

	for (int i = 1; i < argc; ++i) {
		std::string argx = argv[i];
		
		if (argx == "-h" || argx == "--help") {
			show_help();
			return 0;
		} else if (argx == "-v" || argx == "--version") {
			show_ver();
			return 0;
		} else if (argx == "--in-root") {
			if (i + 1 >= argc) {
				std::cerr << "JPM: Error --in-root requires one more parameter.\n";
				return 1;
			}
			i++; //next arg
			ROOT = std::string(argv[i]);
		} else if (argv[i][0] != '-') { //Not starting with "-" it's not a parameter.
			command = std::string(argv[i]);
			if (i + 1 >= argc) {
				std::cerr << "JPM: Error command \"" << command << "\" used but no package name(s) specified.\n";
				return 1;
			}
			i++; //next arg
			pkgs = std::string(argv[i]);
			
			//multi pkg support in feature
			/*i++; //next argument
			while (argv[i][0] != '-') {
				//probably use vectors in feature
				pkgs += std::string(argv[i]) + " ";
				i++; //next argument
			}*/
		}
	}

	// Add JPM package
	if (command == "add") {
		return jpm_add_pkg(pkgs);
	}

	return 0;
}
