#! /bin/bash

cd "${0%/*}"
cd ..

./UpdateDependencies.sh
cmake .
make
