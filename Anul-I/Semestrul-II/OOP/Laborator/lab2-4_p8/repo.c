#include "repo.h"

void initializare(Magazin* m)
{
	/*
	Seteaza dimensiunea logica a depozitului la 0.
	Preconditii:
	- m: pointer valid (m != NULL) catre o structura Magazin.
	Postconditii:
	- m->lungime este setat la 0.
	*/
	m->lungime = 0;
}

int cautare(Magazin* m, int cod)
{
	/*
	Localizeaza indexul unui produs pe baza codului unic.
	Preconditii:
	- m: pointer valid (m != NULL) catre o structura Magazin initializata.
	- cod: numar intreg strict pozitiv.
	Postconditii:
	- Returneaza indexul vectorului (0 <= index < m->lungime) aferent produsului.
	- Returneaza -1 daca entitatea cu codul specificat nu exista.
	*/
	for (int i = 0; i < m->lungime; i++)
	{
		if (m->stoc[i].cod == cod)
		{
			return i;
		}
	}
	return -1;
}

int adaugare(Magazin* m, Produs p)
{
	/*
	Insereaza un produs in depozit.
	Preconditii:
	- m: pointer valid (m != NULL) catre o structura Magazin initializata.
	- p: entitate de tip Produs curent construita.
	Postconditii:
	- Returneaza 1 daca produsul este inserat cu succes, crescand lungimea stocului.
	- Returneaza 0 daca depozitul a atins capacitatea maxima de 100 de elemente, starea structurii ramanand nemodificata.
	*/
	if (m->lungime >= 100)
	{
		return 0;
	}
	m->stoc[m->lungime] = p;
	m->lungime++;
	return 1;
}

int stergere(Magazin* m, int cod)
{
	/*
	Elimina entitatea Produs identificata prin cod din depozit.
	Preconditii:
	- m: pointer valid (m != NULL) catre o structura Magazin initializata.
	- cod: numar intreg strict pozitiv.
	Postconditii:
	- Returneaza 1 si decaleaza elementele subsecvente stanga pentru a acoperi pozitia, decrementand lungimea logica.
	- Returneaza 0 daca entitatea nu exista, structura ramanand intacta.
	*/
	int poz = cautare(m, cod);
	if (poz == -1) 
	{
		return 0;
	}
	for (int i = poz; i < m->lungime - 1; i++)
	{
		m->stoc[i] = m->stoc[i + 1];
	}
	m->lungime--;
	return 1;
}

int actualizare(Magazin* m, Produs p)
{
	/*
	Suprascrie entitatea Produs existenta utilizand o noua structura cu acelasi cod.
	Preconditii:
	- m: pointer valid (m != NULL) catre o structura Magazin initializata.
	- p: structura Produs initializata valid.
	Postconditii:
	- Returneaza 1 in caz de succes.
	- Returneaza 0 daca codul produsului nu exista in depozit.
	*/
	int poz = cautare(m, p.cod);
	if (poz == -1)
	{
		return 0;
	}
	m->stoc[poz] = p;
	return 1;
}

int get_lungime(Magazin* m)
{
	/*
	Furnizeaza numarul de produse distincte din depozit.
	Preconditii:
	- m: pointer valid (m != NULL) catre o structura Magazin initializata.
	Postconditii:
	- Returneaza un numar intreg pozitiv (0 <= m->lungime <= 100).
	*/
	return m->lungime;
}

Produs get_produs(Magazin* m, int index)
{
	/*
	Extrage o copie a structurii Produs de la un index specific.
	Preconditii:
	- m: pointer valid (m != NULL) catre o structura Magazin initializata.
	- index: intreg valid in limitele vectorului (0 <= index < m->lungime).
	Postconditii:
	- Returneaza valoarea structurii Produs de la pozitia ceruta.
	*/
	return m->stoc[index];
}