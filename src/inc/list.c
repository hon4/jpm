#include "list.h"
#include <stdio.h>

#define PKG_FILE "/etc/jpm/pkgs"
#define PKG_MAX_LINE 256

void jpm_list_pkgs() {
	printf("JPM: Installed Packages List\n=============================\n\n");
	
	FILE *fp = fopen(PKG_FILE, "r");
	if (!fp) {
		perror("ERROR: Cannot open required file: " PKG_FILE);
		return;
	}

	char line[PKG_MAX_LINE];

	while (fgets(line, sizeof(line), fp)) {
		// remove newline
		char *nl = line;
		while (*nl) {
			if (*nl == '\n') {
				*nl = '\0';
				break;
			}
			nl++;
		}

		// skip empty lines
		if (line[0] == '\0')
			continue;

		printf("%s\n", line);
	}

	fclose(fp);
	printf("\n");
}