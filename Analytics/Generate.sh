#! /bin/bash

ScriptDirectory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$ScriptDirectory"
cd ..
RootDirectory=$(pwd)

# Build
echo "Building..."
cd "$RootDirectory"
./SetConfiguration.sh -c
make --quiet

if [ $? -ne 0 ] ; then
	exit 1
fi

# Initial
echo "Generating basline zero coverage..."
cd "$ScriptDirectory"
rm -f *.info
lcov --capture --no-external --directory /home/ian/Projects/ionEngine/ --initial --output-file baseline.info --quiet

# Run
echo "Running tests..."
"${RootDirectory}/RunTests.sh"

# Coverage
echo "Running coverage..."
lcov --capture --no-external --directory /home/ian/Projects/ionEngine/ --output-file coverage.info --quiet

# Combine
echo "Finalizing coverage data..."
lcov --add-tracefile coverage.info --add-tracefile baseline.info --output-file combined.info --quiet
lcov --remove combined.info 'Instantiate.h' --output-file final.info --quiet

# Report
echo "Generating report..."
rm -r html
genhtml final.info --output-directory html --quiet
rm -r /var/www/amethyst.iondune.net/public_html/cov
cp -r html /var/www/amethyst.iondune.net/public_html/cov
