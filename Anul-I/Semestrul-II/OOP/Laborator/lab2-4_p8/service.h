#pragma once
#include "repo.h"

int srv_adaugare(Magazin* m, int cod, const char* tip, const char* producator, const char* model, float pret, int cantitate);
int srv_actualizare(Magazin* m, int cod, float pret, int cantitate);
int srv_stergere(Magazin* m, int cod);
Magazin* srv_sort_pret(const Magazin* m, int reverse);
Magazin* srv_sort_cantitate(const Magazin* m, int reverse);
Magazin* srv_filtrare_producator(const Magazin* m, const char* producator);
Magazin* srv_filtrare_pret(const Magazin* m, float pret_min, float pret_max);
Magazin* srv_filtrare_cantitate(const Magazin* m, int cant_min, int cant_max);