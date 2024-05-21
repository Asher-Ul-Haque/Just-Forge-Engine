#!/bin/bash
# Build script for rebuilding all the Just Forge Engine projects
set echo on

echo "Building everything..."

pushd engine
source build.sh
popd

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]; 
then
    echo "Error building Just Forge Engine at errorlevel $ERRORLEVEL"
fi

pushd tester
source build.sh
popd
ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]; 
then
    echo "Error building engine-tester at errorlevel $ERRORLEVEL"
fi

echo "Successfully built everything!"
