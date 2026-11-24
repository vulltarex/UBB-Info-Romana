#pragma once
#include "domain.h"

typedef struct {
	Produs stoc[100];
	int lungime;
}Magazin;

void initializare(Magazin* m);
int cautare(Magazin* m, int cod);
int adaugare(Magazin* m, Produs p);
int stergere(Magazin* m, int cod);
int actualizare(Magazin* m, Produs p);
int get_lungime(Magazin* m);
Produs get_produs(Magazin* m, int index);
