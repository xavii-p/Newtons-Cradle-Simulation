#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Set up Emscripten environment
source /path/to/emsdk/emsdk_env.sh

# Use the full path to CMake if it's not in your PATH
CMAKE_PATH="/Applications/CMake.app/Contents/bin/cmake"

# Explicitly use Ninja
CMAKE_GENERATOR=Ninja

# Update the path to the Emscripten toolchain file
EMSCRIPTEN_TOOLCHAIN="$EMSDK/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake"

# Check if Ninja is available in the system PATH
if ! command -v ninja &> /dev/null
then
    echo "Ninja not found in system PATH. Please ensure Ninja is installed and added to your PATH."
    exit 1
fi

# Configure the project using CMake
$CMAKE_PATH -G $CMAKE_GENERATOR -B build -S . -DCMAKE_TOOLCHAIN_FILE=$EMSCRIPTEN_TOOLCHAIN -DCMAKE_CROSSCOMPILING_EMULATOR=$EMSDK/node/18.20.3_64bit/bin/node

# Check if CMake configuration was successful
if [ $? -ne 0 ]; then
    echo "CMake configuration failed"
    exit 1
fi

# Build the project using Ninja
emmake ninja -C build

# Check if the build was successful
if [ $? -ne 0 ]; then
    echo "Build failed"
    exit 1
fi

echo "Build completed successfully"
