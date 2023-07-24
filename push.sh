#! /bin/bash

function git_add_commit_push() {
    if (($# == 0)) ; then
        echo "error, use this way : './push.sh my git commit message'"
    else
        exec git add *

        commit_message = "git commit -m '"
        for word in $* ; do
            commit_message = "$commit_message $word"
        done
        commit_message = "$commit_message'"

        exec git push 
    fi
}

git_add_commit_push $*