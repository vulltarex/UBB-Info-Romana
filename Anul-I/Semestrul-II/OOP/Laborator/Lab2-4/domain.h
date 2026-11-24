#ifndef DOMAIN_H

#define DOMAIN_H

typedef struct
{
    int cod, cantitate;
    char nume[50];
    float concentratie;

}Medicament;

Medicament creare(int cod, const char* nume, float concentratie, int cantitate);

#endif