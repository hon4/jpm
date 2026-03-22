AC_INIT([jpm], [0.0.1], [greek.team.blog2@gmail.com])
AM_INIT_AUTOMAKE
LT_INIT
AC_PROG_CC

# Check for zlib
AC_CHECK_LIB([z], [gzopen], [have_zlib=yes], [have_zlib=no])
if test "x$have_zlib" = "xno"; then
	AC_MSG_ERROR([zlib not found. Please install zlib development headers])
fi

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
