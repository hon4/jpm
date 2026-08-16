#include "jpm_add_pkg.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include "inc/ensure_dir_exists.hpp"
#include "inc/download_file.hpp"
#include "inc/global_vars.hpp"

int jpm_add_pkg(std::string pkg_name) {

	// Make sure TMP_DIR exists
	if (ensure_dir_exists(TMP_DIR)) {
		std::cerr << "JPM: Error: Temp Directory does not exist and jpm failed to create it.";
		return 1; //Dir does not exist and program Failed to create it.
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
		if (line == pkg_name) {
			packageFound = true;
			break;
		}
	}

	file.close();

	if (!packageFound) {
		std::cerr << "Error: package '" << pkg_name << "' was not found\n";
		std::remove(indexFile.c_str());
		return 1;
	}

	std::cout << "Found package: " << pkg_name << "\n";

	// ------------------------------------------------------------
	// Download package version index
	// ------------------------------------------------------------

	std::string versionIndexFile = TMP_DIR + pkg_name + "-versions.txt";

	std::string versionIndexURL = REPO + "/" + pkg_name + "/versions.txt";

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
		std::cerr << "Error: no versions available for package '" << pkg_name << "'\n";

		std::remove(indexFile.c_str());
		std::remove(versionIndexFile.c_str());

		return 1;
	}

	std::cout << "Latest version: " << latestVersion << "\n";

	// ------------------------------------------------------------
	// Download package
	// ------------------------------------------------------------

	std::string packageFile = pkg_name + "-" + latestVersion + PKG_EXT;

	std::string localPackage = TMP_DIR + packageFile;

	std::string packageURL = REPO + "/" + pkg_name + "/" + latestVersion + PKG_EXT;

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

	if (ensure_dir_exists(ROOT)) {
		std::remove(indexFile.c_str());
		std::remove(versionIndexFile.c_str());
		std::remove(localPackage.c_str());
		return 1; //Dir does not exist and program Failed to create it.
	}

	// ------------------------------------------------------------
	// Extract package
	// ------------------------------------------------------------

	std::cout << "Installing " << pkg_name << " " << latestVersion << " into " << ROOT << "...\n";

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
