#!/bin/bash
if [ $# -lt 1 ]; then
    echo "missing file name"
elif [ $# -gt 1 ]; then
    echo "only one argument is allowed"
else
    file=$1
    if [ -f "$file" ]; then
        echo $(wc -l $file)
	exit 0
    else
        echo "${file_name} not found"
    fi
fi

exit 1
