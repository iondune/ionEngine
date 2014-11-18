#! /bin/bash

ScriptDirectory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$ScriptDirectory"
cd ..

/home/ian/.dotfiles/bin/SyncAndGitPushHgChanges.sh .
