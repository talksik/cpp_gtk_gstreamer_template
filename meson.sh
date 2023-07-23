#!/bin/sh

# incase it's not set up already
meson setup build

echo "Compiling..."
cd build
meson compile

echo "Running..."
./flowy

