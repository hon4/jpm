#include "update_repoindex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "downloadfile.h"

void get_repofiles() {
	FILE *f = fopen(JPM_REPO_FILE, "r");
	if (!f) return;

	char *line = NULL;
	size_t len = 0;

	while (getline(&line, &len, f) != -1) {
		if (line[0] != '#' && line[0] != '\n') {
			printf("%s\n", line);  /* line already has \n */
			line[strcspn(line, "\n")] = 0; /* Remove \n from the end */

			size_t n = strlen(line) + strlen("/x86_64/_index.gz") + 1;
			char file2dl[n];
			snprintf(file2dl, n, "%s%s", line, "/x86_64/_index.gz");
			printf("%s\n", file2dl);

			download_file(file2dl, "/var/cache/jpm/_index.gz");
		}
	}

	free(line);
	fclose(f);
}