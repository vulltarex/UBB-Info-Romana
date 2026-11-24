#pragma once

#include "magazin.h"

/*
   Tipul functie de comparare pentru 2 elemente
   returneaza 0 daca sunt egale, 1 daca p1>p2, -1 altfel
*/
typedef int(*FunctieComparare)(Produs* p1, Produs* p2);


/*
Sorteaza in-place o lista de produse
Pre: m - pointer valid catre o entitate Magazin, cmp_func - relatia dupa care se sorteaza
*/
void sort(Magazin* m, FunctieComparare cmp_func, int reverse);