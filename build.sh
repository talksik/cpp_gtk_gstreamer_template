#!/bin/sh

echo "Building project | making build folder, and going into it..."
rm -rf build
mkdir build
cd build

echo "Running cmake with build type Debug."
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ..

echo "====================="
echo "Running make..."
echo "====================="

make
