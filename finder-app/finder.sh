#!/bin/sh

if [ $# -lt 2 ]
then
    echo "Invalid Arguments"
    exit 1
fi

if [ ! -d "$1" ]
then
    echo "$1 is not a directory"
    exit 1
fi

lines=$(grep -rI  "$2" "$1" | wc -l)
files=$(find "$1" -type f | wc -l)
echo "The number of files are $files and the number of matching lines are $lines"
exit 0
