#! /bin/bash

ScriptDirectory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$ScriptDirectory"

rm -rf xml doxy

make clean

doxygen > /dev/null

~/ext/doxyrest_b/build/doxyrest/bin/Release/doxyrest  xml/index.xml -o doxy/index.rst -F ~/ext/doxyrest_b/doxyrest/frame/ -f c_index.rst.in

make html
