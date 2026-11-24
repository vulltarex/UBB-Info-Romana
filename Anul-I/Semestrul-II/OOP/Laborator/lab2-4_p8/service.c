#include "service.h"
#include "validator.h"
#include <stdlib.h>

int srv_adaugare(Magazin* m, int cod, const char* tip, const char* producator, const char* model, float pret, int cantitate)
{
	/*
	Construieste, valideaza si transfera o entitate Produs catre repozitoriu. In cazul existentei prealabile a codului, valideaza identitatea structurala si cumuleaza stocul.
	Preconditii:
	- m: pointer valid (m != NULL) catre o structura Magazin initializata.
	- cod, cantitate: numere intregi.
	- tip, producator, model: siruri de caractere.
	- pret: numar real.
	Postconditii:
	- Returneaza 1 in caz de adaugare/cumulare cu succes.
	- Returneaza 0 in caz de date invalide, inconsistente la cumulare sau depasire de capacitate.
	*/
	Produs p = creare(cod, tip, producator, model, pret, cantitate);
	if (validare(p) == 0)
	{
		return 0;
	}
	int poz = cautare(m, cod);
	if (poz != -1)
	{
		if (egal(p, get_produs(m, poz)) == 0)
		{
			return 0;
		}
		p.cantitate += get_produs(m, poz).cantitate;
		return actualizare(m, p);
	}
	return adaugare(m, p);
}

int srv_actualizare(Magazin* m, int cod, float pret, int cantitate)
{
	/*
	Valideaza si transfera date noi pentru pret si cantitate asupra unei entitati existente.
	Preconditii:
	- m: pointer valid (m != NULL) catre o structura Magazin initializata.
	- cod, cantitate: numere intregi.
	- pret: numar real.
	Postconditii:
	- Returneaza 1 in caz de actualizare reusita.
	- Returneaza 0 daca datele sunt invalide sau entitatea nu este gasita.
	*/
	int poz = cautare(m, cod);
	if (poz == -1)
	{
		return 0;
	}
	Produs existent = get_produs(m, poz);
	Produs nou = creare(cod, existent.tip, existent.producator, existent.model, pret, cantitate);
	if (!validare(nou))
	{
		return 0;
	}
	return actualizare(m, nou);
}

int srv_stergere(Magazin* m, int cod)
{
	/*
	Transfera instructiunea de eliminare catre repozitoriu pe baza codului unic.
	Preconditii:
	- m: pointer valid (m != NULL) catre o structura Magazin initializata.
	- cod: intreg strict pozitiv.
	Postconditii:
	- Returneaza 1 la stergerea cu succes.
	- Returneaza 0 daca entitatea nu este gasita.
	*/
	return stergere(m, cod);
}

Magazin* srv_sort_pret(const Magazin* m, int reverse)
{
	/*
	Genereaza o copie sortata a depozitului utilizand criteriul pretului.
	Preconditii:
	- m: pointer valid (m != NULL) catre o structura Magazin initializata.
	- reverse: 0 (crescator) sau 1 (descrescator).
	Postconditii:
	- Returneaza un pointer catre o structura Magazin alocata dinamic pe Heap, ordonata cerintelor. Adresa returnata necesita dezalocare explicita via free().
	*/
	Magazin* dto = (Magazin*)malloc(sizeof(Magazin));
	initializare(dto);
	for (int i = 0; i < m->lungime; i++)
	{
		adaugare(dto, m->stoc[i]);
	}
	for (int i = 0; i < dto->lungime; i++)
	{
		for (int j = 0; j < dto->lungime - 1; j++)
		{
			if (reverse == 0 && dto->stoc[j].pret > dto->stoc[j + 1].pret || reverse == 1 && dto->stoc[j].pret < dto->stoc[j + 1].pret)
			{
				Produs aux = dto->stoc[j];
				dto->stoc[j] = dto->stoc[j + 1];
				dto->stoc[j + 1] = aux;
			}
		}
	}
	return dto;
}

Magazin* srv_sort_cantitate(const Magazin* m, int reverse)
{
	/*
	Genereaza o copie sortata a depozitului utilizand criteriul cantitatii.
	Preconditii:
	- m: pointer valid (m != NULL) catre o structura Magazin initializata.
	- reverse: 0 (crescator) sau 1 (descrescator).
	Postconditii:
	- Returneaza un pointer catre o structura Magazin alocata dinamic pe Heap, ordonata cerintelor. Adresa returnata necesita dezalocare explicita via free().
	*/
	Magazin* dto = (Magazin*)malloc(sizeof(Magazin));
	initializare(dto);
	for (int i = 0; i < m->lungime; i++)
	{
		adaugare(dto, m->stoc[i]);
	}
	for (int i = 0; i < dto->lungime; i++)
	{
		for (int j = 0; j < dto->lungime - 1; j++)
		{
			if (reverse == 0 && dto->stoc[j].cantitate > dto->stoc[j + 1].cantitate || reverse == 1 && dto->stoc[j].cantitate < dto->stoc[j + 1].cantitate)
			{
				Produs aux = dto->stoc[j];
				dto->stoc[j] = dto->stoc[j + 1];
				dto->stoc[j + 1] = aux;
			}
		}
	}
	return dto;
}

Magazin* srv_filtrare_producator(const Magazin* m, const char* producator)
{
	/*
	Genereaza o structura care izoleaza entitatile pe baza producatorului specificat.
	Preconditii:
	- m: pointer valid (m != NULL) catre o structura Magazin initializata.
	- producator: sir nevid de caractere.
	Postconditii:
	- Returneaza un pointer catre o structura Magazin alocata dinamic, populata strict cu rezultatele cautarii. Necesita eliberarea memoriei prin free().
	*/
	Magazin* dto = (Magazin*)malloc(sizeof(Magazin));
	initializare(dto);
	for (int i = 0; i < m->lungime; i++)
	{
		if (strcmp(m->stoc[i].producator, producator) == 0)
		{
			adaugare(dto, m->stoc[i]);
		}
	}
	return dto;
}

Magazin* srv_filtrare_pret(const Magazin* m, float pret_min, float pret_max)
{
	/*
	Genereaza o structura care izoleaza entitatile pe baza unui interval de pret definit de doua limite incluzive.
	Preconditii:
	- m: pointer valid (m != NULL) catre o structura Magazin initializata.
	- pret_min, pret_max: numere reale strict pozitive (pret_min <= pret_max).
	Postconditii:
	- Returneaza un pointer catre o structura Magazin alocata dinamic, populata strict cu rezultatele cautarii. Necesita eliberarea memoriei prin free().
	*/
	Magazin* dto = (Magazin*)malloc(sizeof(Magazin));
	initializare(dto);
	for (int i = 0; i < m->lungime; i++)
	{
		if (m->stoc[i].pret >= pret_min && m->stoc[i].pret <= pret_max)
		{
			adaugare(dto, m->stoc[i]);
		}
	}
	return dto;
}

Magazin* srv_filtrare_cantitate(const Magazin* m, int cant_min, int cant_max)
{
	/*
	Genereaza o structura care izoleaza entitatile pe baza unui interval de cantitate definit de doua limite incluzive.
	Preconditii:
	- m: pointer valid (m != NULL) catre o structura Magazin initializata.
	- cant_min, cant_max: numere intregi strict pozitive (cant_min <= cant_max).
	Postconditii:
	- Returneaza un pointer catre o structura Magazin alocata dinamic, populata strict cu rezultatele cautarii. Necesita eliberarea memoriei prin free().
	*/
	Magazin* dto = (Magazin*)malloc(sizeof(Magazin));
	initializare(dto);
	for (int i = 0; i < m->lungime; i++)
	{
		if (m->stoc[i].cantitate >= cant_min && m->stoc[i].cantitate <= cant_max)
		{
			adaugare(dto, m->stoc[i]);
		}
	}
	return dto;
}
