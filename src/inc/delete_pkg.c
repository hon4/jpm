#include "delete_pkg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "remove_line.h"

int delete_pkg(const char *pkgname) {
	int ret = 0;

	ret = remove_line("/etc/jpm/pkgs", pkgname);
	if (ret != 0) {
		return ret;
	}

	/* strmrg */
	char *varlibpath = "/var/lib/jpm/pkgs/";
	char *contendpath = "/contents";
	size_t len = strlen(varlibpath) + strlen(pkgname) + strlen(contendpath) + 1;
	/* Allocate memory */
    char *merged = (char *)malloc(len);
    if (merged == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
	/* Copy and concatenate */
    strcpy(merged, varlibpath);   // copy str1
    strcat(merged, pkgname);   // append str2
    strcat(merged, contendpath);   // append str3
	/* strmrg end */
	
	FILE *file = fopen(merged, "r");  // Open file in read mode
	if (file == NULL) {
		perror("Error opening file");
		return 1;
	}

	char line[1024];  // Buffer to store each line
	while (fgets(line, sizeof(line), file)) {
		/* fgets includes the newline char */
		printf("%s", line);
	}

	fclose(file);
	return 0;
}