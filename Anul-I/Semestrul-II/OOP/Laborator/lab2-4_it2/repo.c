#include "repo.h"

void initializare(Magazin* m)
{
	*m = create_empty();
}

int cautare(Magazin* m, int cod)
{
	for (int i = 0; i < size(m); i++)
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
	add(m, p);
	return 1;
}

int stergere(Magazin* m, int cod)
{
	int poz = cautare(m, cod);
	if (poz == -1)
	{
		return 0;
	}
	remove_elem(m, poz);
	return 1;
}

int actualizare(Magazin* m, Produs p)
{
	int poz = cautare(m, p.cod);
	if (poz == -1)
	{
		return 0;
	}
	set_elem(m, p, poz);
	return 1;
}

int get_lungime(const Magazin* m)
{
	return size(m);
}

Produs get_produs(const Magazin* m, int index)
{
	return get_elem(m, index);
}