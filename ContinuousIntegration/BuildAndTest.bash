#!/usr/bin/env bash

cd "${0%/*}"
cd ..

./Clean.bash
./UpdateDependencies.bash

mkdir Build
cd Build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
./bin/TestConfig
./bin/TestUnits
