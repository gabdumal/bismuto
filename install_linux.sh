#!/bin/bash

# Clear previous installation
sudo rm /usr/local/bin/bismuto
sudo rm -rf /usr/local/share/bismuto

# Create a build directory in /tmp
TEMP_DIR=/tmp/bismuto_build
rm -rf $TEMP_DIR
mkdir $TEMP_DIR

# Check if the argparse library is installed
if [ ! -f /usr/local/lib/libargparse.a ]; then
    # Create a build directory for the argparse library
    ARGPARSE_TEMP_DIR=/tmp/argparse_build
    rm -rf $ARGPARSE_TEMP_DIR
    mkdir $ARGPARSE_TEMP_DIR

    # Clone the argparse repository
    git clone https://github.com/p-ranav/argparse $ARGPARSE_TEMP_DIR
    cd $ARGPARSE_TEMP_DIR

    # Build the argparse library
    mkdir build
    cd build
    cmake -DARGPARSE_BUILD_SAMPLES=on -DARGPARSE_BUILD_TESTS=on ..
    make

    # Install the argparse library
    sudo make install

    # Cleanup
    rm -rf $ARGPARSE_TEMP_DIR
fi

# Configure
cmake -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE --no-warn-unused-cli -S . -B $TEMP_DIR/build -G Ninja

# Build
cmake --build $TEMP_DIR/build --config Release --target all --

# Install
sudo cmake --install $TEMP_DIR/build --config Release

# Cleanup
rm -rf $TEMP_DIR
