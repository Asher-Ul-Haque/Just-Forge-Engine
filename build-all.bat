ECHO "Building everything..."

PUSHD engine
CALL build.bat
POPD
@REM PUSHD engine
@REM CALL build.bat
@REM POPD
@REM IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

@REM PUSHD testbed
@REM CALL build.bat
@REM POPD
@REM IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

REM Engine
make -f "Makefile.engine.windows.mak" all
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

PUSHD testbed
CALL build.bat
POPD
REM Testbed
make -f "Makefile.testbed.windows.mak" all
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)


ECHO "Built everything!"
