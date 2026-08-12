#include "download_file.hpp"
#include <curl/curl.h>
#include <iostream>
#include <string>

bool download_file(const std::string& url, const std::string& path) {
	CURL* curl = curl_easy_init();
	if (!curl) {
		std::cerr << "curl_easy_init failed\n";
		return false;
	}

	FILE* file = fopen(path.c_str(), "wb");
	if (!file) {
		std::cerr << "Cannot open output file: " << path << "\n";
		curl_easy_cleanup(curl);
		return false;
	}

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

	CURLcode result = curl_easy_perform(curl);

	long http_code = 0;
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

	fclose(file);
	curl_easy_cleanup(curl);

	if (result != CURLE_OK) {
		std::cerr << "Download failed: " << curl_easy_strerror(result) << "\n";
		return false;
	}

	std::cout << "HTTP status: " << http_code << "\n";
	std::cout << "Downloaded: " << path << "\n";

	return http_code >= 200 && http_code < 300;
}
