#!/bin/sh

echo "[ INFO ] Cleaning Compiled *.o files."
rm src/inc/*.o
rm src/*.o

echo "[ INFO ] Cleaning Makefiles"
rm src/Makefile
rm src/Makefile.in
rm Makefile
rm Makefile.in

echo "[ INFO ] Cleaning binaries"
rm src/jpm

echo "[ INFO ] Cleaning autoconf/automake/libtool temp files"
rm INSTALL
rm aclocal.m4
rm -rf autom4te.cache
rm compile
rm config.guess
rm config.log
rm config.status
rm config.sub
rm configure
rm configure~
rm depcomp
rm install-sh
rm libtool
rm ltmain.sh
rm missing
rm config.guess~
rm config.sub~
rm -rf src/.deps
rm -rf src/.libs
rm -rf src/inc/.deps
rm src/inc/.dirstamp
