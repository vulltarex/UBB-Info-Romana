#pragma once
#include "repo.h"

int cmp_pret(Produs* p1, Produs* p2);

int cmp_cantitate(Produs* p1, Produs* p2);

/*
Controleaza fluxul de creare, validare si stocare a unui produs. Aplica cumularea stocului in caz de entitate existenta.
Pre: m - pointer valid la Magazin. Date individuale pentru constructia entitatii Produs.
Post: Returneaza 1 pentru operatiune reusita. Returneaza 0 pentru date invalide sau nepotrivire structurala la cumulare.
*/
int srv_adaugare(Magazin* m, int cod, const char* tip, const char* producator, const char* model, float pret, int cantitate);

/*
Controleaza fluxul de actualizare a proprietatilor pret si cantitate pentru o entitate existenta.
Pre: m - pointer valid la Magazin. cod - intreg identificator. pret, cantitate - noi valori atribuibile.
Post: Returneaza 1 in caz de actualizare validata si aplicata. Returneaza 0 in caz de esec de validare sau absenta entitate.
*/
int srv_actualizare(Magazin* m, int cod, float pret, int cantitate);

/*
Transmite comanda stergere a unui element identificat prin cod.
Pre: m - pointer valid la Magazin. cod - intreg > 0.
Post: Returneaza 1 in caz de succes, 0 daca entitatea lipseste.
*/
int srv_stergere(Magazin* m, int cod);

/*
Extrage si ordoneaza continutul depozitului utilizand pretul ca si criteriu comparativ.
Pre: m - pointer valid la Magazin. reverse - indicator directional (0 - crescator, 1 - descrescator).
Post: Returneaza o instanta Magazin alocata pe Heap, continand copiile sortate. Necestia apel explicit la destroy() urmat de free() in modulul apelant.
*/
Magazin* srv_sort_pret(const Magazin* m, int reverse);

/*
Extrage si ordoneaza continutul depozitului utilizand cantitatea disponibila ca si criteriu comparativ.
Pre: m - pointer valid la Magazin. reverse - indicator directional (0 - crescator, 1 - descrescator).
Post: Returneaza o instanta Magazin alocata pe Heap, continand copiile sortate. Necesita apel explicit la destroy() urmat de free() in modulul apelant.
*/
Magazin* srv_sort_cantitate(const Magazin* m, int reverse);

/*
Izoleaza entitatile care satisfac criteriul de egalitate integrala fata de producatorul indicat.
Pre: m - pointer valid la Magazin. producator - sir de caractere.
Post: Returneaza o instanta Magazin alocata pe Heap, populata exclusiv cu entitatile calificate. Necesita distrugere manuala.
*/
Magazin* srv_filtrare_producator(const Magazin* m, const char* producator);

/*
Izoleaza entitatile al caror pret se incadreaza intre limitele transmise ca parametru (inclusiv).
Pre: m - pointer valid la Magazin. pret_min, pret_max - numere reale > 0.
Post: Returneaza o instanta Magazin alocata pe Heap continand setul rezultat. Necesita distrugere manuala. Permite interschimbarea automata a limitelor daca sunt furnizate invers.
*/
Magazin* srv_filtrare_pret(const Magazin* m, float pret_min, float pret_max);

/*
Izoleaza entitatile a caror cantitate disponibila se incadreaza intre limitele transmise ca parametru (inclusiv).
Pre: m - pointer valid la Magazin. cant_min, cant_max - numere intregi > 0.
Post: Returneaza o instanta Magazin alocata pe Heap continand setul rezultat. Necesita distrugere manuala. Permite interschimbarea automata a limitelor daca sunt furnizate invers.
*/
Magazin* srv_filtrare_cantitate(const Magazin* m, int cant_min, int cant_max);