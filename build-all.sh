#!/bin/bash
# Build script for rebuilding all the Just Forge Engine projects
set echo on
mkdir -p build/
touch build/Just_Forge_Engine.so

echo "Building everything..."

make -f Makefile.engine.linux.mak all

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]; 
then
    echo "Error building Just Forge Engine at errorlevel $ERRORLEVEL" && exit $ERRORLEVEL
fi

make -f Makefile.tester.linux.mak all
ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]; 
then
    echo "Error building engine-tester at errorlevel $ERRORLEVEL" && exit $ERRORLEVEL
fi

echo "Successfully built everything!"
