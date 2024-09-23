#!/bin/bash

if   [[ "$#" -lt 1 ]]; then
    echo "missing file name"
    exit
elif [[ "$#" -gt 1 ]]; then
    echo "only one argument is allowed"
    exit
else
    lines=0
    while read line;
    do
        (( lines += 1 ))
    done < $1
    echo "$lines"
fi
exit 0
# vim: set fenc=utf8 ff=unix et sw=2 ts=2 sts=2: