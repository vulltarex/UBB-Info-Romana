#!/bin/bash

if [ $# -ne 3 ]; then
	echo "Trei (3) argumente!"
else
	ps -e | grep -E "[2-9]([0-9])*:" > $1
	ps -e | grep -E " 00:" > $2
	ps -e | grep -E "^( )*3([0-9]){4,4} " > $3
fi
