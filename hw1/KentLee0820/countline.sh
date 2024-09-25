##!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "error: wrong argument"
else
    filename="$1"
    if [ -f "$filename" ]; then
        line_count=$(wc -l < "$filename")
        echo "$line_count"
    else
        echo "error: $filename not found"
    fi
fi
