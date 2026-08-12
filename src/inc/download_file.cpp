#include "download_file.hpp"
#include <iostream>

bool download_file(const std::string& url, const std::string& output) {
    std::string command = "curl -L -f -sS -o \"" + output + "\" \"" + url + "\"";

    int result = std::system(command.c_str());

    return result == 0;
}
