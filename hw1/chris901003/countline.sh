#!/bin/bash

if [ "$#" -lt 1 ]; then
    echo "missing file name"
    exit 1
elif [ "$#" -gt 1 ]; then
    echo "only one argument is allowed"
    exit 1
fi

file="$1"

if [ ! -f "$file" ]; then
    echo "$file not found"
    exit 1
fi

line_count=$(wc -l < "$file")
echo "$line_count lines in $file"