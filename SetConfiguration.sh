#! /bin/bash

RootDirectory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

if [ -z "$1" ] ; then
	echo "usage: ./SetConfiguration.sh <configuration>"
	exit 1
fi

CurrentConfiguration=
if [ -f "$RootDirectory/.configuration.mk" ] ; then
	CurrentConfiguration=$(sed 's/CONFIGURATION=//' "$RootDirectory/.configuration.mk")
fi

Set ()
{
	if [ "$1" != "$CurrentConfiguration" ] ; then
		echo "Changing configuration from $CurrentConfiguration to $1"
	fi
	echo "CONFIGURATION=$1" > "$RootDirectory/.configuration.mk"
}

if [ "$1" = "Debug" ] || [ "$1" = "-d" ] ; then
	Set "Debug"
elif [ "$1" = "Release" ] || [ "$1" = "-r" ] ; then
	Set "Release"
elif [ "$1" = "Coverage" ] || [ "$1" = "-c" ] ; then
	Set "Coverage"
else
	echo "Unknown configuration: $1"
	exit 1
fi
