#!/bin/sh

# Clean the env.
scons -c

# Build and scan.
if [ -z "$1" ]
then
    scan-build-7 -k -maxloop 25 --use-c++=g++ --use-cc=gcc -enable-checker alpha -enable-checker nullability -enable-checker security scons -k
else
    scan-build-7 -k -maxloop 25 --use-c++=g++ --use-cc=gcc -enable-checker alpha -enable-checker nullability -enable-checker security -o $1 scons -k
fi
