#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <filesystem>
#include "inc/show_ver_help.hpp"

//#define JPM_VERSION "0.0.1" moved to show_ver_help.cpp

namespace fs = std::filesystem;

const std::string REPO = "http://192.168.1.4/repo";
const std::string ROOT = "/fakeroot";
const std::string PKG_EXT = ".jpm";
const std::string TMP_DIR = "/tmp/jpm/";

bool downloadFile(const std::string& url, const std::string& output) {
    std::string command = "curl -L -f -sS -o \"" + output + "\" \"" + url + "\"";

    int result = std::system(command.c_str());

    return result == 0;
}

int main(int argc, char* argv[]) {
	/*if (argc == 1) {
		printf("JPM: No command. Type -h to show help.\n");
		return 1;
	}*/

    // Check command
    if (argc != 3 || std::string(argv[1]) != "add") {
        std::cout << "Usage: jpm add <package>\n";
        return 1;
    }

    std::string packageName = argv[2];

	// Make sure TMP_DIR exists
    try {
        fs::create_directories(TMP_DIR);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error creating " << TMP_DIR << ": " << e.what() << "\n";
        return 1;
    }

	// Temporary index file
    std::string indexFile = TMP_DIR + "jpm-index.txt";

    std::cout << "Downloading package index...\n";

    if (!downloadFile(REPO + "/index.txt", indexFile)) {
        std::cerr << "Error: could not download index.txt\n";
        return 1;
    }

    // Open index
    std::ifstream file(indexFile);

    if (!file) {
        std::cerr << "Error: could not open index.txt\n";
        return 1;
    }

    // Find package
    std::string line;
    std::string packageFile;

    while (std::getline(file, line)) {
        // Remove possible CR in CRLF files
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        // Package names are assumed to be:
        // name-version
        //
        // For now, simply check whether the line starts
        // with the requested package name.

        if (line.rfind(packageName + "-", 0) == 0)
        {
            packageFile = line;
            break;
        }
    }

    file.close();

    if (packageFile.empty()) {
        std::cerr << "Error: package '" << packageName << "' was not found\n";
        return 1;
    }

    std::cout << "Found package: " << packageFile << "\n";

    // Download package
    std::string localPackage = TMP_DIR + packageFile + PKG_EXT;

    std::string packageURL = REPO + "/" + packageFile + PKG_EXT;

    std::cout << "Downloading " << packageFile << PKG_EXT << "...\n";

    if (!downloadFile(packageURL, localPackage)) {
        std::cerr << "Error: could not download package\n";
        return 1;
    }

    // Make sure /fakeroot exists
    try {
        fs::create_directories(ROOT);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error creating " << ROOT << ": "
                  << e.what() << "\n";
        return 1;
    }

    // Extract package
    std::cout << "Installing package into " << ROOT << "...\n";

    std::string extractCommand =
        "tar -xzf \"" + localPackage +
        "\" -C \"" + ROOT + "\"";

    int result = std::system(extractCommand.c_str());

    if (result != 0) {
        std::cerr << "Error: could not extract package\n";
        return 1;
    }

    std::cout << "Package installed successfully!\n";

	std::remove(indexFile.c_str());
	std::remove(localPackage.c_str());

    return 0;
}
