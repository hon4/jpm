#include "download_file.hpp"
#include <curl/curl.h>

bool download_file(const std::string& url, const std::string& path) {
    CURL* curl = curl_easy_init();
    if (!curl)
        return false;

    FILE* file = fopen(path.c_str(), "wb");
    if (!file) {
        curl_easy_cleanup(curl);
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    CURLcode result = curl_easy_perform(curl);

    fclose(file);
    curl_easy_cleanup(curl);

    return result == CURLE_OK;
}
