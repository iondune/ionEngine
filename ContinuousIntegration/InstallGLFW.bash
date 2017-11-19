#!/usr/bin/env bash

git clone https://github.com/glfw/glfw
cd glfw/
mkdir build
cd build/
cmake -DBUILD_SHARED_LIBS=ON ..
make -j4
sudo make install
