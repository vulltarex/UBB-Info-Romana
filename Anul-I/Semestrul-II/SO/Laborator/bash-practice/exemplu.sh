#!/bin/bash

if [ $# -ne 4 ]; then
	echo "Numar incorect de argumente."
    echo "Utilizare: ./exemplu.sh file1 file2 file3 file4"
else
    cuvinte="$(cat "$1" | tr -cs 'a-zA-z0-9' '\n')"
    echo "$cuvinte" | grep -E "^[aeiouAEIOU].*[^aeiouAEIOU0-9]$" > "$2"
    echo "$cuvinte" | grep -E "[0-9]" > "$3"
    echo "$(cat "$2" | wc -l ) cuvinte gasite ce incep cu vocala si se termina in cosnoana" > "$4"
    echo "$(cat "$3" | wc -l) cuvinte ce contin minim o cifra" >> "$4"
    for word in $cuvinte; do
	    nr_litere=$(echo $word | tr -cd 'a-zA-Z' | wc -c)
	    nr_cifre=$(echo $word | tr -cd '0-9' | wc -c)
	if echo $word | grep -Eq "^[aeiouAEIOU].*[^aeiouAEIOU0-9]$"; then
	    criteriu="incepe cu vocala se termina cu consoana"
	    echo "$word $criteriu $nr_litere litere $nr_cifre cifre" >> "$4"
	fi
	if echo $word | grep -q "[0-9]"; then
	    criteriu="contine cel putin o cifra"
	    echo "$word $criteriu $nr_litere litere $nr_cifre cifre" >> "$4"
	fi	    
    done
fi
