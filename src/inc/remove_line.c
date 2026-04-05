#include "remove_line.h"
#include <stdio.h>
#include <stdlib.h>

int remove_line(const char *filename, const char *line_content) {
	FILE *file = fopen(filename, "r");
	if (!file) {
		perror("Error opening file");
		return -1;
	}

	FILE *temp = fopen("temp.txt", "w");
	if (!temp) {
		perror("Error creating temp file");
		fclose(file);
		return -1;
	}

	char buffer[1024];

	while (fgets(buffer, sizeof(buffer), file)) {
		/* Remove newline character for comparison */
		buffer[strcspn(buffer, "\r\n")] = 0;

		/* Only write lines that do NOT match the target */
		if (strcmp(buffer, line_content) != 0) {
			fprintf(temp, "%s\n", buffer);
		}
	}

	fclose(file);
	fclose(temp);

	/* Replace original file with temp file */
	if (remove(filename) != 0) {
		perror("Error removing original file");
		return -1;
	}
	if (rename("temp.txt", filename) != 0) {
		perror("Error renaming temp file");
		return -1;
	}

	return 0;
}