#include "downloadfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ensure_dir.h"

int download_file(const char *url, const char *outfile) {
	char *lastslash;
	if ((lastslash = strrchr(outfile, '/'))) {
		printf("Directory path: %.*s\n", (int)(lastslash - outfile), outfile);
		//*lastslash = '\0'; /* NULL terminate outfile at last slash to make it dir path */
		//printf("aaa\n");
		//ensure_dir(outfile);
		//*lastslash = '/'; /* Return the slash to make it file path again as it was */
	}

	char cmd[1024];
	int n = snprintf(cmd, sizeof(cmd), "wget -O \"%s\" \"%s\"", outfile, url);
	if (n < 0 || n >= (int)sizeof(cmd)) {
		fprintf(stderr, "URL or filename too long\n");
		return 1;
	}
	return system(cmd);
}