#include "download_file.hpp"
#include <iostream>

bool download_file(const std::string& url, const std::string& output) {
	std::string command;
	//First check if it's a local path.
	if (url[0] == '/' || url[0] == '~') {
		command = "cp " + url + " " + output;
	} else {
		command = "curl -L -f -sS -o \"" + output + "\" \"" + url + "\"";
	}
	int result = std::system(command.c_str());

	return result == 0;
}
