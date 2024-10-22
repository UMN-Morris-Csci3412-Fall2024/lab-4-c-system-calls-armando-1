#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <path>"
    exit 1
fi

path=$1
#will store the path argument if given
if [ ! -d "$path" ]; then
    echo "Error: $path is not a valid."
    exit 1
fi
#if there is error it will exit out

num_dirs=$(find "$path" -type d | wc -l)
#will count num of directories and regular files with find & wc 
num_regular=$(find "$path" -type f | wc -l)
#prints any final counts
echo "There were $num_dirs directories."
echo "There were $num_regular regular files."
