#include "remove_line.h"
#include <stdio.h>
#include <stdlib.h>

int remove_line(const char *filename, int line_to_remove) {
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
    int current_line = 1;

    while (fgets(buffer, sizeof(buffer), file)) {
        if (current_line != line_to_remove) {
            fputs(buffer, temp);
        }
        current_line++;
    }

    fclose(file);
    fclose(temp);

    /* Replace original file */
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