@echo off

REM Run from root directory!
if not exist "%cd%\build\assets\shaders\" mkdir "%cd%\build\assets\shaders"

echo "Compiling shaders..."

echo "Assets/shaders/Builtin.ObjectShader.vert.glsl -> build/assets/shaders/Builtin.ObjectShader.vert.spv"
%VULKAN_SDK%\bin\glslc.exe -fshader-stage=vert assets/shaders/Builtin.ObjectShader.vert.glsl -o bin/assets/shaders/Builtin.ObjectShader.vert.spv
IF %ERRORLEVEL% NEQ 0 (echo Error: %ERRORLEVEL% && exit)

echo "assets/shaders/Builtin.ObjectShader.frag.glsl -> build/assets/shaders/Builtin.ObjectShader.frag.spv"
%VULKAN_SDK%\bin\glslc.exe -fshader-stage=frag assets/shaders/Builtin.ObjectShader.frag.glsl -o build/assets/shaders/Builtin.ObjectShader.frag.spv
IF %ERRORLEVEL% NEQ 0 (echo Error: %ERRORLEVEL% && exit)

echo "Copying assets..."
echo xcopy "assets" "build\assets" /h /i /c /k /e /r /y
xcopy "assets" "build\assets" /h /i /c /k /e /r /y

echo "Done."
