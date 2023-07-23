#!/bin/sh

# incase it's not set up already
meson setup build

echo "Compiling..."
cd build
meson compile


echo "Placing compile_commands.json in root directory..."
rm ../compile_commands.json
cp compile_commands.json ../

echo "Running..."
./flowy

