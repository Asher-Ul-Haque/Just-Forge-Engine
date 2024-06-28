#!/bin/bash

# Check if glslc exists
if [ ! -x "$VULKAN_SDK/bin/glslc" ]; then
    echo "Error: glslc not found or not executable at $VULKAN_SDK/bin/glslc"
    exit 1
fi

# Run from root directory!
mkdir -p build/Assets
mkdir -p build/Assets/shaders

echo "Compiling shaders..."

echo "Assets/shaders/Builtin.ObjectShader.vert.glsl -> build/Assets/shaders/Builtin.ObjectShader.vert.spv"
$VULKAN_SDK/bin/glslc -fshader-stage=vert Assets/shaders/Builtin.ObjectShader.vert.glsl -o build/Assets/shaders/Builtin.ObjectShader.vert.spv
ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
    echo "Error:"$ERRORLEVEL && exit $ERRORLEVEL
fi

echo "Assets/shaders/Builtin.ObjectShader.frag.glsl -> build/Assets/shaders/Builtin.ObjectShader.frag.spv"
$VULKAN_SDK/bin/glslc -fshader-stage=frag Assets/shaders/Builtin.ObjectShader.frag.glsl -o build/Assets/shaders/Builtin.ObjectShader.frag.spv
ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
    echo "Error:"$ERRORLEVEL && exit $ERRORLEVEL
fi

echo "Copying Assets..."
cp -R "Assets" "build"

echo "Done."
