#include "install_jpm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "append2file.h"
#include "ensure_dir.h"

/* Adds the package to sthe system */
int add_jpm(const char *jpmfile, const char *targetdir) {
	int ret = 0;
	ret = install_jpm(jpmfile, targetdir);
	if (ret != 0) {
		return ret;
	}
	
	ret = append2file("/etc/jpm/pkgs", jpmfile);
	if (ret != 0) {
		return ret;
	}
	
	/* probably fix shorten ?? */
	ret = ensure_dir("/var/lib/jpm");
	if (ret != 0) {
		return ret;
	}
	ret = ensure_dir("/var/lib/jpm/pkgs");
	if (ret != 0) {
		return ret;
	}
	ret = ensure_dir("/var/lib/jpm/pkgs/jpm");
	if (ret != 0) {
		return ret;
	}
	/* end probably shorten */
	
	char command[512]; /* probably fix the limit */
	snprintf(command, sizeof(command), "tar -tf %s > /var/lib/jpm/pkgs/jpm/contents", jpmfile);

	return system(command);
}

int install_jpm(const char *jpmfile, const char *targetdir) {
	if (targetdir == NULL || strlen(targetdir) == 0) {
		targetdir = "/";
	}
	
	char command[512]; /* probably fix the limit */
	snprintf(command, sizeof(command), "tar -xf %s -C %s", jpmfile, targetdir);

	return system(command);
}