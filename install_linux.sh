#!/bin/bash

# Clear previous installation
sudo rm /usr/local/bin/bismuto
sudo rm -rf /usr/local/share/bismuto

# Create a build directory in /tmp
BUILD_DIR=/tmp/bismuto_build
rm -rf $BUILD_DIR

# Configure
cmake -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_TOOLCHAIN_FILE=cmake/linux.cmake --no-warn-unused-cli -S . -B $BUILD_DIR -G Ninja

# Build
cmake --build $BUILD_DIR --config Release --target all --

# Install
sudo cmake --install $BUILD_DIR --config Release

# Cleanup
rm -rf $BUILD_DIR
