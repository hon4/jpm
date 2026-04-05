#include "install_jpm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int install_jpm(const char *jpmfile, const char *targetdir) {
	if (targetdir == NULL || strlen(targetdir) == 0) {
		targetdir = "/";
	}
	
	char command[512]; /* probably fix the limit */
	snprintf(command, sizeof(command), "tar -xf %s -C %s", jpmfile, targetdir);

	return system(command);
}