#!/bin/bash
set -e

# Check for correct input
if [ "$#" -ne 1 ] || { [ "$1" != "Debug" ] && [ "$1" != "Release" ]; }; then
    echo "Usage: $0 <Debug|Release>"
    exit 1
fi

BUILD_TYPE=$1

# Create necessary directories
mkdir -p bin/linux
cd bin/linux

# Configure and build
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ../..
make

# Return to the original directory
cd ../..
