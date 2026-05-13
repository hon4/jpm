AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = jpm
jpm_SOURCES = main.cpp \
		inc/list.c \
		inc/downloadfile.c \
		inc/gzdecompress.c \
		inc/update_repoindex.c \
		inc/ensure_dir.c \
		inc/install_jpm.c \
		inc/append2file.c \
		inc/delete_pkg.c \
		inc/remove_line.c

jpm_LDADD = -lz
