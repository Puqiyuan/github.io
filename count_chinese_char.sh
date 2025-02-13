#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 <directory>"
    exit 1
fi

dir="$1"

#count=$(find "$dir" -type f -exec grep -oP '[\p{Han}]' {} + | wc -l)
count=$(find "$dir" -type f -name "*.org" -print0 | \
    xargs -0 grep -oP '[\p{Han}]' 2>/dev/null | wc -l)

echo "Total Chinese characters count in '$dir': $count"

