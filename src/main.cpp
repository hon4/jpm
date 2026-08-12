#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include "inc/show_ver_help.hpp"
#include "inc/download_file.hpp"

//#define JPM_VERSION "0.0.1" moved to show_ver_help.cpp

namespace fs = std::filesystem;

const std::string REPO = "http://192.168.1.4/repo/amd64";
const std::string ROOT = "/fakeroot";
const std::string PKG_EXT = ".jpm";
const std::string TMP_DIR = "/tmp/jpm/";

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

    // ------------------------------------------------------------
    // Download main package index
    // ------------------------------------------------------------

    std::string indexFile = TMP_DIR + "index.txt";

    std::cout << "Downloading package index...\n";

    if (!download_file(REPO + "/index.txt", indexFile)) {
        std::cerr << "Error: could not download index.txt\n";
        return 1;
    }

    // Open index
    std::ifstream file(indexFile);

    if (!file) {
        std::cerr << "Error: could not open index.txt\n";
        return 1;
    }

    // ------------------------------------------------------------
    // Find package name
    // ------------------------------------------------------------

    std::string line;
    bool packageFound = false;

    while (std::getline(file, line)) {
        // Remove possible CR in CRLF files
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        // Exact package name match
        if (line == packageName) {
            packageFound = true;
            break;
        }
    }

    file.close();

    if (!packageFound) {
        std::cerr << "Error: package '" << packageName << "' was not found\n";
        std::remove(indexFile.c_str());
        return 1;
    }

    std::cout << "Found package: " << packageName << "\n";

    // ------------------------------------------------------------
    // Download package version index
    // ------------------------------------------------------------

    std::string versionIndexFile = TMP_DIR + packageName + "-versions.txt";

    std::string versionIndexURL = REPO + "/" + packageName + "/versions.txt";

    std::cout << "Downloading version list...\n";

    if (!download_file(versionIndexURL, versionIndexFile)) {
        std::cerr << "Error: could not download versions.txt\n";
        std::remove(indexFile.c_str());
        return 1;
    }

    // Open version index
    std::ifstream versionFile(versionIndexFile);

    if (!versionFile) {
        std::cerr << "Error: could not open versions.txt\n";
        std::remove(indexFile.c_str());
        std::remove(versionIndexFile.c_str());
        return 1;
    }

    // ------------------------------------------------------------
    // Find latest version
    // ------------------------------------------------------------

    std::string version;
    std::string latestVersion;

    while (std::getline(versionFile, version)) {
        // Remove possible CR in CRLF files
        if (!version.empty() && version.back() == '\r')
            version.pop_back();

        if (!version.empty()) {
            latestVersion = version;
        }
    }

    versionFile.close();

    if (latestVersion.empty()) {
        std::cerr << "Error: no versions available for package '" << packageName << "'\n";

        std::remove(indexFile.c_str());
        std::remove(versionIndexFile.c_str());

        return 1;
    }

    std::cout << "Latest version: " << latestVersion << "\n";

    // ------------------------------------------------------------
    // Download package
    // ------------------------------------------------------------

    std::string packageFile = packageName + "-" + latestVersion + PKG_EXT;

    std::string localPackage = TMP_DIR + packageFile;

    std::string packageURL = REPO + "/" + packageName + "/" + latestVersion + PKG_EXT;

    std::cout << "Downloading " << packageFile << "...\n";

    if (!download_file(packageURL, localPackage)) {
        std::cerr << "Error: could not download package\n";

        std::remove(indexFile.c_str());
        std::remove(versionIndexFile.c_str());

        return 1;
    }

    // ------------------------------------------------------------
    // Make sure ROOT exists
    // ------------------------------------------------------------

    try {
        fs::create_directories(ROOT);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error creating " << ROOT << ": " << e.what() << "\n";

        std::remove(indexFile.c_str());
        std::remove(versionIndexFile.c_str());
        std::remove(localPackage.c_str());

        return 1;
    }

    // ------------------------------------------------------------
    // Extract package
    // ------------------------------------------------------------

    std::cout << "Installing " << packageName << " " << latestVersion << " into " << ROOT << "...\n";

    std::string extractCommand = "tar -xzf \"" + localPackage + "\" -C \"" + ROOT + "\"";

    int result = std::system(extractCommand.c_str());

    if (result != 0) {
        std::cerr << "Error: could not extract package\n";

        std::remove(indexFile.c_str());
        std::remove(versionIndexFile.c_str());
        std::remove(localPackage.c_str());

        return 1;
    }

    std::cout << "Package installed successfully!\n";

    // ------------------------------------------------------------
    // Clean up temporary files
    // ------------------------------------------------------------

    std::remove(indexFile.c_str());
    std::remove(versionIndexFile.c_str());
    std::remove(localPackage.c_str());

    return 0;
}
