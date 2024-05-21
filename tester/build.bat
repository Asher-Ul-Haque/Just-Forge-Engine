REM Build script for testbed
@ECHO OFF
SetLocal EnableDelayedExpansion

REM Get a list of all the .c files.
SET cFilenames=
FOR /R %%f in (*.c) do (
    SET cFilenames=!cFilenames! %%f
)

REM echo "Files:" %cFilenames%

SET assembly=Just_Forge_Tester
SET compilerFlags=-g 
REM -Wall -Werror
SET includeFlags=-Isrc -I../engine/src/
SET linkerFlags=-L../build/ -lJust_Forge_Engine.lib
SET defines=-D_DEBUG -DFORGE_IMPORT

ECHO "Building %assembly%%..."
clang %cFilenames% %compilerFlags% -o ../build/%assembly%.exe %defines% %includeFlags% %linkerFlags%
