ECHO "Building everything..."

MKDIR build
PUSHD Just_Forge_Engine
CALL build.bat
POPD
@REM PUSHD engine
@REM CALL build.bat
@REM POPD
@REM IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

@REM PUSHD Just_Forge_Tester
@REM CALL build.bat
@REM POPD
@REM IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

REM Engine
make -f "Makefile.engine.windows.mak" all
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

PUSHD Just_Forge_Tester
CALL build.bat
POPD
REM Testbed
make -f "Makefile.testbed.windows.mak" all
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

ECHO "Successfull built everything!"
PUSHD build
CALL Just_Forge_Tester.exe
POPD
