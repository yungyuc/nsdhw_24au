#!/bin/bash

case "$#" in
    0) echo "missing file name" ;;
    1)
        fname="$1"
        if [ -f "$fname" ]; then
            echo "$(wc -l < "$fname") lines in $fname"
        else
            echo "$fname not found"
        fi
        ;;
    *) echo "only one argument is allowed" ;;
esac