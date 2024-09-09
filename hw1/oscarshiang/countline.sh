#!/bin/bash

if [[ "$#" -lt "1" ]]; then
    echo "missing file name"
elif [[ "$#" -gt "1" ]]; then
    echo "only one argument is allowed"
else
    FNAME=$1
    if [[ -f "$FNAME" ]]; then
        LINES=$(cat $FNAME | wc -l | xargs)
        echo "$LINES lines in $FNAME"
    else
        echo "$FNAME not found"
    fi
fi
