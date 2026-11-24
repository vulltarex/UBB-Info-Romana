#include "domain.h"
#include <string.h>

Medicament creare(int cod, const char* nume, float concentratie, int cantitate)
{
    Medicament m;
    m.cod = cod;
    strncpy(m.nume, nume, 49);
    m.concentratie = concentratie;
    m.cantitate = cantitate;

    return m;
}