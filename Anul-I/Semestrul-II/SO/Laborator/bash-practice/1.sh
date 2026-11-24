#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Introduceti exact doua argumente."
    echo "Utilizare: ./1.sh file1 file2 "
    exit 1
fi
> "$2"

while read U A T; do
    if [ "$U" != "root" ] && [ "$A" = "LOGIN" ] && [ "$T" -gt 30 ]; then
	echo "Alerta: Utilizatorul $U a fost conectat $T minute" >> "$2"
    fi
done < "$1"
	
