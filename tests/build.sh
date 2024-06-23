#!/bin/bash
# Build Script for the testbed
set echo on

mkdir -p ../build

cd ..
make -f Makefile.tests.linux.mak all
ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]; 
then
    echo "Error building tests at errorlevel $ERRORLEVEL" && exit $ERRORLEVEL
fi
echo "Successfully built tests"
cd tests/
