#!/bin/bash

while read f1 f2; do
    if test -e "$f1"; then
        rm "$f2"
    fi
done < a.txt
