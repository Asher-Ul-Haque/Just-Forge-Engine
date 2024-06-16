#!/bin/bash
# Build script for testbed
set echo on

mkdir -p ../build

# Get a list of all the .c files.
cFilenames=$(find . -type f -name "*.c")

# echo "Files:" $cFilenames

assembly="Just_Forge_Tester"
compilerFlags="-g -fdeclspec -fPIC" 
# -fms-extensions 
# -Wall -Werror
includeFlags="-Isrc -I../engine/src/"
linkerFlags="-L../build/ -lJust_Forge_Engine -Wl,-rpath,."
defines="-D_DEBUG -DFORGE_IMPORT"

echo "Building $assembly..."
echo clang $cFilenames $compilerFlags -o ../build/$assembly $defines $includeFlags $linkerFlags
clang $cFilenames $compilerFlags -o ../build/$assembly $defines $includeFlags $linkerFlags
