#! /bin/bash

ScriptDirectory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$ScriptDirectory"
cd ..
RootDirectory=$(pwd)

# Build
cd "$RootDirectory"
./SetConfiguration.sh -c
make --quiet

if [ $? -ne 0 ] ; then
	exit 1
fi

# Initial
cd "$ScriptDirectory"
rm -f *.info
lcov --capture --no-external --directory /home/ian/Projects/ionEngine/ --initial --output-file baseline.info

# Run
"${RootDirectory}/RunTests.sh"

# Coverage
lcov --capture --no-external --directory /home/ian/Projects/ionEngine/ --output-file coverage.info

# Combine
lcov --add-tracefile coverage.info --add-tracefile baseline.info --output-file combined.info
lcov --remove combined.info 'Instantiate.h' --output-file final.info

# Report
rm -r html
genhtml final.info --output-directory html
rm -r /var/www/amethyst.iondune.net/public_html/cov
cp -r html /var/www/amethyst.iondune.net/public_html/cov
