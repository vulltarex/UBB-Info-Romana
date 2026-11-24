#include "service.h"
#include "validator.h"
#include "sortare.h"
#include <stdlib.h>
#include <string.h>

int cmp_pret(Produs* p1, Produs* p2)
{
	if (p1->pret > p2->pret) return 1;
	if (p1->pret < p2->pret) return -1;
	return 0;
}

int cmp_cantitate(Produs* p1, Produs* p2)
{
	if (p1->cantitate > p2->cantitate) return 1;
	if (p1->cantitate < p2->cantitate) return -1;
	return 0;
}

int srv_adaugare(Magazin* m, int cod, const char* tip, const char* producator, const char* model, float pret, int cantitate)
{
	Produs p = creare(cod, tip, producator, model, pret, cantitate);
	if (validare(p) == 0)
	{
		destroy_produs(&p);
		return 0;
	}
	int poz = cautare(m, cod);
	if (poz != -1)
	{
		Produs p_nou = get_produs(m, poz);
		if (egal(p, p_nou) == 0)
		{
			destroy_produs(&p_nou);
			destroy_produs(&p);
			return 0;
		}
		p.cantitate += p_nou.cantitate;
		destroy_produs(&p_nou);
		return actualizare(m, p);
	}
	return adaugare(m, p);
}

int srv_actualizare(Magazin* m, int cod, float pret, int cantitate)
{
	int poz = cautare(m, cod);
	if (poz == -1)
	{
		return 0;
	}
	Produs existent = get_produs(m, poz);
	Produs nou = creare(cod, existent.tip, existent.producator, existent.model, pret, cantitate);
	destroy_produs(&existent);
	if (!validare(nou))
	{
		destroy_produs(&nou);
		return 0;
	}
	return actualizare(m, nou);
}

int srv_stergere(Magazin* m, int cod)
{
	return stergere(m, cod);
}

Magazin* srv_sort_pret(const Magazin* m, int reverse)
{
	Magazin* dto = (Magazin*)malloc(sizeof(Magazin));
	initializare(dto);
	for (int i = 0; i < get_lungime(m); i++)
	{
		adaugare(dto, get_produs(m, i));
	}
	sort(dto, cmp_pret, reverse);
	return dto;
}

Magazin* srv_sort_cantitate(const Magazin* m, int reverse)
{
	Magazin* dto = (Magazin*)malloc(sizeof(Magazin));
	initializare(dto);
	for (int i = 0; i < get_lungime(m); i++)
	{
		adaugare(dto, get_produs(m, i));
	}
	sort(dto, cmp_cantitate, reverse);
	return dto;
}

Magazin* srv_filtrare_producator(const Magazin* m, const char* producator)
{
	Magazin* dto = (Magazin*)malloc(sizeof(Magazin));
	initializare(dto);
	for (int i = 0; i < get_lungime(m); i++)
	{
		Produs p = get_produs(m, i);
		if (strcmp(p.producator, producator) == 0)
		{
			adaugare(dto, p);
		}
		else
		{
			destroy_produs(&p);
		}
	}
	return dto;
}

Magazin* srv_filtrare_pret(const Magazin* m, float pret_min, float pret_max)
{
	Magazin* dto = (Magazin*)malloc(sizeof(Magazin));
	initializare(dto);
	if (pret_min > pret_max)
	{
		float aux = pret_min;
		pret_min = pret_max;
		pret_max = aux;
	}
	for (int i = 0; i < get_lungime(m); i++)
	{
		Produs p = get_produs(m, i);
		if (p.pret >= pret_min && p.pret <= pret_max)
		{
			adaugare(dto, p);
		}
		else
		{
			destroy_produs(&p);
		}
	}
	return dto;
}

Magazin* srv_filtrare_cantitate(const Magazin* m, int cant_min, int cant_max)
{
	Magazin* dto = (Magazin*)malloc(sizeof(Magazin));
	initializare(dto);
	if (cant_min > cant_max)
	{
		int aux = cant_min;
		cant_min = cant_max;
		cant_max = aux;
	}
	for (int i = 0; i < get_lungime(m); i++)
	{
		Produs p = get_produs(m, i);
		if (p.cantitate >= cant_min && p.cantitate <= cant_max)
		{
			adaugare(dto, p);
		}
		else
		{
			destroy_produs(&p);
		}
		
	}
	return dto;
}
