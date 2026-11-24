#include "domain.h"
#include <string.h>

Produs creare(int cod, const char* tip, const char* producator, const char* model, float pret, int cantitate)
{
	/*
	Creeaza o entitate de tip produs
	Preconditii:
	- cod: intreg strict pozitiv
	- tip, producator, model: siruri de caractere nevide
	- pret: real strict pozitiv
	- cantitate: intreg strict pozitiv
	Postconditii:
	- Returneaza o structura Produs initializata cu atributele transmise
	- Sirurile de caractere care depasesc 49 de elemente sunt trunchiate
	*/
	Produs p;
	p.cod = cod;
	strncpy_s(p.tip, sizeof(p.tip), tip, 49);
	strncpy_s(p.producator, sizeof(p.producator), producator, 49);
	strncpy_s(p.model, sizeof(p.model), model, 49);
	p.pret = pret;
	p.cantitate = cantitate;

	return p;
}

int egal(Produs p, Produs other)
{
	/*
	Verifica daca doua entitati de tip Produs sunt identice, ignorand campul cantitate.
	Preconditii:
	- p, other: entitati de tip Produs initializate
	Postconditii:
	- Returneaza 1 daca atributele cod, tip, producator, model si pret sunt identice
	- Returneaza 0 altfel
	*/
	if (p.cod != other.cod) return 0;
	if (strcmp(p.tip, other.tip) != 0) return 0;
	if (strcmp(p.producator, other.producator) != 0) return 0;
	if (strcmp(p.model, other.model) != 0) return 0;
	if (p.pret != other.pret) return 0;
	return 1;
}