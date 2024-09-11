#!/bin/bash

if [ $# -lt 1 ]; then
    echo "missing file name";
elif [ $# -gt 1 ]; then
    echo "only one argument is allowed";
else
    FILE_NAME=$1
    FILE_EXIST=$(ls ${FILE_NAME} > /dev/null 2>&1; echo $?)
    if [ ${FILE_EXIST} = 0 ]; then
        FILE_LINE_COUNT=$(cat ${FILE_NAME} 2>/dev/null | wc -l);
        echo ${FILE_LINE_COUNT} lines in ${FILE_NAME};
    else
        echo ${FILE_NAME} not found;
    fi
fi