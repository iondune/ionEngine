#! /bin/bash

# Build
cd /home/ian/Projects/ionEngine/TestCore
make remake

if [ $? -ne 0 ] ; then
	exit 1
fi

# Initial
cd /home/ian/Projects/ionEngine/Profiling
lcov --capture --no-external --directory /home/ian/Projects/ionEngine/ --initial --output-file basline.info

# Run
cd /home/ian/Projects/ionEngine/TestCore
./Coverage/TestCore

# Coverage
cd /home/ian/Projects/ionEngine/Profiling
lcov --capture --no-external --directory /home/ian/Projects/ionEngine/ --output-file coverage.info

# Combine
lcov --add-tracefile coverage.info --add-tracefile basline.info --output-file combined.info

# Report
rm -r html
genhtml combined.info --output-directory html
rm -r /var/www/amethyst.iondune.net/public_html/cov
cp -r html /var/www/amethyst.iondune.net/public_html/cov
