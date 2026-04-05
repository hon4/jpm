#include "append2file.h"
#include <stdio.h>

int append2file(const char *filename, const char *line) {
	FILE *file = fopen(filename, "a"); /* a = Open file in append mode */
	if (file == NULL) {
		perror("Failed to open file");
		return 1;
	}

	/* Append text + newline */
	if (fprintf(file, "%s\n", line) < 0) {
		perror("Failed to write to file");
		fclose(file);
		return 1;
	}

	fclose(file);
	return 0;
}