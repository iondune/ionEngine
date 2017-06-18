#! /bin/bash

ScriptDirectory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$ScriptDirectory"

rm -rf html
lessc extra.less extra.css
doxygen > /dev/null
