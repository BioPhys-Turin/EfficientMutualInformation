rm -rf build
mkdir -p build
cd build
export CXXFLAGS="-std=c++14 -O3 -Wall -Wextra -Wpedantic -Werror"
cmake ..
make
mv local/src/hk .
mkdir -p $PREFIX/bin
cp hk $PREFIX/bin/
