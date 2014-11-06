#! /bin/bash

tests=TestCore

RootDirectory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$RootDirectory"

Configuration=$(GetConfiguration.sh)

for test in $tests ; do
	echo "--- Running test $test ------------------------------------------"
	"$test/$Configuration/$test"
done
