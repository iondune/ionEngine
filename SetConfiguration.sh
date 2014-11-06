#! /bin/bash

if [ -z "$1" ] ; then
	echo "usage: ./SetConfiguration.sh <configuration>"
	exit 1
fi

RootDirectory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$RootDirectory"
CurrentConfiguration=$(GetConfiguration.sh)

Set ()
{
	echo "CONFIGURATION=$1" > ".configuration.mk"
	if [ "$1" != "$CurrentConfiguration" ] ; then
		echo "Changed configuration from $CurrentConfiguration to $1"
	fi
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
