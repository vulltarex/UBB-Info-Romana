#include "repo.h"

void initializare(Farmacie* f)
{
    f->lungime = 0;
}

int cautare(Farmacie* f, int cod)
{
    for (int i = 0; i < f->lungime; i++)
    {
        if (f->stoc[i].cod == cod)
        {
            return i;
        }
    }
    return -1;
}

int adaugare(Farmacie* f, Medicament m)
{
    if (f->lungime >= 100)
    {
        return 0;
    }
    f->stoc[f->lungime] = m;
    f->lungime++;
    return 1;
}

int actualizare(Farmacie* f, Medicament m)
{
    int poz = cautare(f, m.cod);
    if (poz == -1)
    {
        return 0;
    }
    f->stoc[poz] = m;
    return 1;
}

int stergere(Farmacie* f, int cod)
{
    int poz = cautare(f, cod);
    if (poz == -1)
    {
        return 0;
    }
    for (int i = poz; i < f->lungime - 1; i++)
    {
        f->stoc[i] = f->stoc[i + 1];
    }
    f->lungime--;
    return 1;
}

int get_lungime(Farmacie* f)
{
    return f->lungime;
}

Medicament get_medicament(Farmacie* f, int index)
{
    return f->stoc[index];
}