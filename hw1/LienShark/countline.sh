#!/bin/bash
# 計算行數 wc -l -w -m 分別計算行數 字數 字元數
lines=$(wc -l < "$1" | sed 's/^[ \t]*//')
if [ $lines -eq 0 ]; then
    echo "something error,maybe you missing your file name"
else
    echo "This file has $lines line"
fi
