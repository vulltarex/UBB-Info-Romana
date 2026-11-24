#include "service.h"
#include "validator.h"

int srv_adaugare(Farmacie* f, int cod, const char* nume, float concentratie, int cantitate)
{
    Medicament m = creare(cod, nume, concentratie, cantitate);
    if (validare(m) == 0)
    {
        return 0;
    }
    int poz = cautare(f, m.cod);
    if (poz != -1)
    {
        Medicament existent = get_medicament(f, poz);
        existent.cantitate += cantitate;
        return actualizare(f, existent);
    }
    return adaugare(f, m);
}

int srv_actualizare(Farmacie* f, int cod, const char* nume_nou, float concentratie_noua) {
    int poz = cautare(f, cod);
    if (poz == -1)
    {
        return 0;
    }
    Medicament existent = get_medicament(f, poz);
    Medicament m = creare(cod, nume_nou, concentratie_noua, existent.cantitate);
    if (!validare(m))
    {
        return 0;
    }
    return actualizare(f, m);
}

int srv_stergere(Farmacie* f, int cod)
{
    return stergere(f, cod);
}

Farmacie srv_filtrare_cantitate(Farmacie* f, int cantitate_max)
{
    Farmacie rez;
    initializare(&rez);
    for (int i = 0; i < get_lungime(f); i++)
    {
        if (get_medicament(f, i).cantitate < cantitate_max)
        {
            adaugare(&rez, f->stoc[i]);
        }
    }
    return rez;
}

Farmacie srv_filtrare_litera(Farmacie* f, char litera)
{
    Farmacie rez;
    initializare(&rez);
    for (int i = 0; i < get_lungime(f); i++)
    {
        if (get_medicament(f, i).nume[0] == litera)
        {
            adaugare(&rez, f->stoc[i]);
        }
    }
    return rez;
}

Farmacie srv_sortat_nume(Farmacie* f)
{
    Farmacie rez = *f;
    for (int i = 0; i < get_lungime(&rez); i++)
    {
        for (int j = i + 1; j < get_lungime(&rez) - 1; j++)
        {

        }
    }

    return rez;
}