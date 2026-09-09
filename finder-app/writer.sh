#!/bin/bash

if [ $# -lt 2 ]
then
	echo "Invalid Arguments"
	exit 1
fi


if ! mkdir -p "$(dirname "$1")"
then
    echo "Could not create directory" >&2
    exit 1
fi

if ! echo "$2" > "$1"
then
    echo "Could not write to $1" >&2
    exit 1
fi

exit 0
