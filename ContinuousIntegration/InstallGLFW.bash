#!/usr/bin/env bash

git clone https://github.com/glfw/glfw
cd glfw/
mkdir build
cd build/
cmake ..
make -j4
sudo make install
