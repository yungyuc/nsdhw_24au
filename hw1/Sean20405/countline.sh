#!/usr/bin/bash

if [ $# -ne 1 ]; then
    echo "missing file name"
elif [ $# -gt 1 ]; then
    echo "only one argument is allowed"
else
    if [ -e $1 ]; then
        echo "`wc -l $1 | awk '{print $1}'` lines in $1"
    else
        echo "$1 does not exist"
    fi
fi
