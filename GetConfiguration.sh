#! /bin/bash

RootDirectory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$RootDirectory"

if [ ! -f ".configuration.mk" ] ; then
	make ".configuration.mk"
fi
sed 's/CONFIGURATION=//' ".configuration.mk"
