#!/usr/bin/env bash

git clone https://github.com/glfw/glfw
cd glfw/
mkdir build
cd build/
if [ "$1" = "--shared" ]; then
	cmake -DBUILD_SHARED_LIBS=ON ..
else
	cmake ..
fi
make -j4
sudo make install
