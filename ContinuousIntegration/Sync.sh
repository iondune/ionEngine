#! /bin/bash

ScriptDirectory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$ScriptDirectory"
cp hgrc ../.hg/hgrc

cd ..

/home/ian/.dotfiles/bin/SyncAndGitPushHgChanges.sh .
