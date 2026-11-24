#ifndef SERVICE_H

#define SERVICE_H
#include "repo.h"

int srv_adaugare(Farmacie* f, int cod, const char* nume, float concentratie, int cantitate);
int srv_actualizare(Farmacie* f, int cod, const char* nume_nou, float concentratie_noua);
int srv_stergere(Farmacie* f, int cod);
Farmacie srv_filtrare_cantitate(Farmacie* f, int cantitate_max);
Farmacie srv_filtrare_litera(Farmacie* f, char litera);
Farmacie srv_sortat_nume(Farmacie *f);
Farmacie srv_sortat_cantitate(Farmacie *f);

#endif