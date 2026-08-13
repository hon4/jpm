#!/bin/sh

echo "Reading from internal storage"
cd ~ && cp -r storage/shared/jpm . && cd jpm
echo "OK"

echo "Running autogen.sh"
./autogen.sh
echo "OK"

echo "Running configure"
./configure --prefix=$PREFIX
echo "OK"

echo "Running make"
make -j$(nproc)
echo "OK"
