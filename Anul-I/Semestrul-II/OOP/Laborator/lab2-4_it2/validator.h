#pragma once
#include "domain.h"

/*
Valideaza starea interna a unei entitati Produs.
Pre: p - entitate Produs.
Post: Returneaza 1 daca toate regulile de domeniu sunt respectate (valori strict pozitive, siruri nevide). Returneaza 0 altfel.
*/
int validare(Produs p);