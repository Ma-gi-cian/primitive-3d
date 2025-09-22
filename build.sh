#!/bin/bash

rm primitive-3d

rm -rf build
mkdir build
cd build 
cmake ..

make -j5
../primitive-3d
