#include "ensure_dir_exists.hpp"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int ensure_dir_exists(std::string dir_path) {
	try {
		fs::create_directories(dir_path);
	} catch (const fs::filesystem_error& e) {
		std::cerr << "Error creating " << dir_path << ": " << e.what() << "\n";
		return 1;
	}
	return 0;
}
