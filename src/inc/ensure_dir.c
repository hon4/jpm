#include "ensure_dir.h"
#include <sys/stat.h>
#include <stdio.h>

int ensure_dir(const char *d) {
	struct stat st;
	if (stat(d, &st) == 0) return 0;	/* dir exists exists. ok */
	return mkdir(d, 0755);				/* dir not exists. create */
}