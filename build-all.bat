@ECHO OFF
REM Build Everything

REM Make sure build directory exists
IF NOT EXIST build (MKDIR build)

ECHO "Building everything..."


PUSHD engine
CALL build.bat
POPD
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

PUSHD tester
CALL build.bat
POPD
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

ECHO "Successfully built everything!"
