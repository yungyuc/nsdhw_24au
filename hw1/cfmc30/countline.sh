#/usr/bin/env bash

if [ "$#" -lt 1 ]; then
    echo "missing file name\n"
    exit
elif [ "$#" -gt 1 ]; then
    echo "only one argument is allowed\n"
    exit
fi

lines=0
while read -r line; do lines=$(($lines + 1)) ; done < $1
echo $lines
