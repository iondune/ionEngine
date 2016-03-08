#!/usr/bin/env bash

cd "${0%/*}"
cd ..

hg bookmark --rev stable release
hg bookmark --rev default master
hg push git+ssh://git@github.com:iondune/ionEngine.git
