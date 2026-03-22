#include "update_repoindex.h"
#include <stdio.h>

void get_repofiles() {
	FILE *f = fopen(JPM_REPO_FILE, "r");
    if (!f) return 1;

    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, f) != -1) {
        if (line[0] != '#' && line[0] != '\n')
            printf("%s", line);  /* line already has \n */
    }

    free(line);
    fclose(f);
	//download_file(const char *url, const char *outfile);
}