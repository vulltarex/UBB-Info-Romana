#!/bin/bash

if [ $# -ne 3 ]; then
	echo "Error: provide exactly 3 arguments"
	echo "Usage: $0 arg1 arg2 arg3"
	exit 1
else
	echo "$1"
	echo "$2"
	echo "$3"
	echo "total: $#"
fi
