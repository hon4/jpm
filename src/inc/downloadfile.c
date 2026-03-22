#include "downloadfile.h"
#include <stdio.h>

int download_file(const char *url, const char *outfile) {
    char cmd[1024];
    int n = snprintf(cmd, sizeof(cmd), "wget -O \"%s\" \"%s\"", outfile, url);
    if (n < 0 || n >= (int)sizeof(cmd)) {
        fprintf(stderr, "URL or filename too long\n");
        return 1;
    }
    return system(cmd);
}