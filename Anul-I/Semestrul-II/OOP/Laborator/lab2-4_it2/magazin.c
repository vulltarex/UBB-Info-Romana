#include "magazin.h"
#include <stdlib.h>

Magazin create_empty()
{
	Magazin lista;
	lista.lungime = 0;
	lista.capacitate = 2;
	lista.stoc = (Produs*)malloc(lista.capacitate * sizeof(Produs));
	return lista;
}

void resize(Magazin* m)
{
	int capacitate_noua = 2 * m->capacitate;
	Produs* stoc_nou = (Produs*)malloc(capacitate_noua * sizeof(Produs));
	for (int i = 0; i < m->lungime; i++)
	{
		stoc_nou[i] = m->stoc[i];
	}
	free(m->stoc);
	m->stoc = stoc_nou;
	m->capacitate = capacitate_noua;
}

void add(Magazin* m, Produs p)
{
	if (m->lungime == m->capacitate)
	{
		resize(m);
	}
	m->stoc[m->lungime++] = p;
}

int size(const Magazin* m)
{
	return m->lungime;
}

void remove_elem(Magazin* m, int index)
{
	destroy_produs(&m->stoc[index]);
	for (int i = index; i < m->lungime - 1; i++)
	{
		m->stoc[i] = m->stoc[i + 1];
	}
	m->lungime--;
}

Produs get_elem(const Magazin* m, int index)
{
	return copy_produs(&m->stoc[index]);
}

void destroy(Magazin* m)
{
	for (int i = 0; i < m->lungime; i++)
	{
		destroy_produs(&m->stoc[i]);
	}
	free(m->stoc);
	m->lungime = 0;
	m->capacitate = 0;
}

void set_elem(Magazin* m, Produs p, int index)
{
	destroy_produs(&m->stoc[index]);
	m->stoc[index] = p;
}
