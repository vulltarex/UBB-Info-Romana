#include "validator.h"
#include <string.h>

int validare(Medicament m)
{
    if (m.cod < 0) return 0;
    if (strlen(m.nume) == 0) return 0;
    if (m.concentratie <= 0) return 0;
    if (m.cantitate <= 0) return 0;
    return 1;
}