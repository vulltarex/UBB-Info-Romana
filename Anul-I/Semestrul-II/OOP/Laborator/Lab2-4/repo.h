#ifndef REPO_H
#define REPO_H
#include "domain.h"

typedef struct
{
    Medicament stoc[100];
    int lungime;
}Farmacie;

void initializare(Farmacie* f);
int cautare(Farmacie* f, int cod);
int adaugare(Farmacie* f, Medicament m);
int actualizare(Farmacie* f, Medicament m);
int stergere(Farmacie* f, int cod);
int get_lungime(Farmacie* f);
Medicament get_medicament(Farmacie* f, int index);

#endif