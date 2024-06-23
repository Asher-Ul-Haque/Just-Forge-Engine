#!/bin/bash

# Run from root directory!
mkdir -p build/assets
mkdir -p build/assets/shaders

echo "Compiling shaders..."

echo "Assets/shaders/Builtin.ObjectShader.vert.glsl -> build/assets/shaders/Builtin.ObjectShader.vert.spv"
$VULKAN_SDK/bin/glslc -fshader-stage=vert assets/shaders/Builtin.ObjectShader.vert.glsl -o build/assets/shaders/Builtin.ObjectShader.vert.spv
ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error:"$ERRORLEVEL && exit
fi

echo "assets/shaders/Builtin.ObjectShader.frag.glsl -> build/assets/shaders/Builtin.ObjectShader.frag.spv"
$VULKAN_SDK/bin/glslc -fshader-stage=frag assets/shaders/Builtin.ObjectShader.frag.glsl -o build/assets/shaders/Builtin.ObjectShader.frag.spv
ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error:"$ERRORLEVEL && exit
fi

echo "Copying assets..."
echo cp -R "assets" "build"
cp -R "assets" "build"

echo "Done."
