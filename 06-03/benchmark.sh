#!/bin/bash

COMPILER=clang++-18
FLAGS="-std=c++20 -O2"
TIME_CMD="/usr/bin/time -f %e"

echo "Benchmark: Headers vs Modules (Clang 18)"

# --- HEADERS ---
echo
echo "[ HEADERS APPROACH ]"
mkdir -p build_headers
cd build_headers

echo "1. Compiling Rational.cpp (includes big header)..."
$TIME_CMD $COMPILER $FLAGS -c ../headers/Rational.cpp -o Rational.o

echo "2. Compiling main.cpp (includes big header)..."
$TIME_CMD $COMPILER $FLAGS -c ../headers/main.cpp -o main.o

echo "3. Linking..."
$TIME_CMD $COMPILER Rational.o main.o -o app_headers

echo
echo "Object Sizes:"
du -h Rational.o main.o
echo "Executable Size:"
du -h app_headers

cd ..

# --- MODULES ---
echo
echo "[ MODULES APPROACH ]"
mkdir -p build_modules
cd build_modules

# 1. RationalMixins (Partition)
echo "1a. Precompiling RationalMixins.cppm..."
$TIME_CMD $COMPILER $FLAGS --precompile ../modules/RationalMixins.cppm -o RationalMixins.pcm

echo "1b. Compiling RationalMixins.pcm to Object..."
$TIME_CMD $COMPILER $FLAGS -c RationalMixins.pcm -o RationalMixins.o

# 2. Rational (Interface)
echo "2a. Precompiling Rational.cppm (includes big header)..."
$TIME_CMD $COMPILER $FLAGS --precompile ../modules/Rational.cppm -fmodule-file=rational:mixins=RationalMixins.pcm -o Rational.pcm

# 2b. Compiling Rational.pcm to Object...
echo "2b. Compiling Rational.pcm to Object..."
$TIME_CMD $COMPILER $FLAGS -c Rational.pcm -fmodule-file=rational:mixins=RationalMixins.pcm -o RationalInterface.o

# 3. Rational (Implementation)
echo "3. Compiling Rational.cpp (implementation)..."
$TIME_CMD $COMPILER $FLAGS -c ../modules/Rational.cpp -fmodule-file=rational=Rational.pcm -fmodule-file=rational:mixins=RationalMixins.pcm -o RationalImpl.o

# 4. Main
echo "4. Compiling main.cpp (importing module)..."
$TIME_CMD $COMPILER $FLAGS -c ../modules/main.cpp -fmodule-file=rational=Rational.pcm -fmodule-file=rational:mixins=RationalMixins.pcm -o main.o

# 5. Link
echo "5. Linking (All objects)..."
$TIME_CMD $COMPILER RationalMixins.o RationalInterface.o RationalImpl.o main.o -o app_modules

echo
echo "Object & PCM Sizes:"
du -h RationalMixins.pcm Rational.pcm Rational.o main.o
echo "Executable Size:"
du -h app_modules

cd ..

echo
echo "========================================"
echo "Done."