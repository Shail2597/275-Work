#!/bin/bash

if [[ "$#" -eq 0 ]]; then
    echo "Usage: ./testDescribe <test_set_file>" >&2
    exit 1
fi

for stem in $(cat "$1"); do
    echo "Description for test case '$stem':"
    desc_file="$stem.desc"
    if [[ -f "$desc_file" ]]; then
        cat "$desc_file"
    else
        echo "$stem: No test description available"
    fi
done