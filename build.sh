#!/bin/bash
set -e
export CXXFLAGS="-std=c++14 -O3 -Wall -Wextra -Wpedantic -Werror"

rm -rf build
mkdir -p build
cd build

# Use the environment CXXFLAGS instead of hardcoding them here
# This allows conda-build to set appropriate flags
# export CXXFLAGS="-std=c++14 -O3 -Wall -Wextra -Wpedantic -Werror"

cmake ${CMAKE_ARGS} ..
make

# Create the bin directory and install the executable
mkdir -p ${PREFIX}/bin
cp local/src/hk ${PREFIX}/bin/
