#pragma once
#include "domain.h"
#include "magazin.h"

/*
Initializeaza depozitul prin instantierea vectorului intern.
Pre: m - pointer valid la memorie alocata pentru structura Magazin.
Post: Structura de la adresa m devine o instanta valida si goala de vector dinamic.
*/
void initializare(Magazin* m);

/*
Localizeaza un produs pe baza codului unic de identificare.
Pre: m - pointer valid la Magazin. cod - intreg > 0.
Post: Returneaza indexul elementului in vector daca exista. Returneaza -1 daca nu exista.
*/
int cautare(Magazin* m, int cod);

/*
Executa inserarea unui produs in depozit.
Pre: m - pointer valid la Magazin, p - entitate Produs validata.
Post: Returneaza 1 in urma adaugarii cu succes.
*/
int adaugare(Magazin* m, Produs p);

/*
Executa eliminarea unui produs din depozit pe baza codului unic.
Pre: m - pointer valid la Magazin. cod - intreg > 0.
Post: Returneaza 1 in caz de stergere cu succes. Returneaza 0 daca elementul nu exista.
*/
int stergere(Magazin* m, int cod);

/*
Inlocuieste o entitate existenta cu una noua care poseda acelasi cod.
Pre: m - pointer valid la Magazin. p - entitate Produs validata.
Post: Returneaza 1 in caz de actualizare cu succes. Returneaza 0 daca produsul nu este localizat.
*/
int actualizare(Magazin* m, Produs p);

/*
Ofera abstractizarea dimensiunii depozitului curent.
Pre: m - pointer valid la Magazin.
Post: Returneaza numarul curent de elemente stocate.
*/
int get_lungime(const Magazin* m);

/*
Ofera abstractizarea accesului la date strict prin index.
Pre: m - pointer valid la Magazin. index apartine intervalului valid.
Post: Returneaza elementul Produs de la pozitia indicata.
*/
Produs get_produs(const Magazin* m, int index);
