#!/bin/bash

if [ $# -ne 3 ]; then
    echo "Numar incorect de argumente"
    echo "Utilizare: ./2.sh file1 file2 file3"
    exit 1
fi

if [ ! -f "$1" ]; then
   echo "Fisier de intrare inexistent!"
   exit 1
fi

> "$2"
> "$3"
cnt_upper=0
cnt_semn=0
while read line; do
    if echo "$line" | grep -q "^[A-Z]"; then
	echo "$line" >> "$2"
	((cnt_upper++))
   fi
   if echo "$line" | grep -q "?$"; then
	echo "$line" >> "$3"
	((cnt_semn++))
   fi
done < "$1"

echo "$cnt_upper linii incep cu litera mare"
echo "$cnt_semn linii se termina cu ?"
