#include "ui.h"
#include <stdio.h>

void print_meniu()
{
    printf("1. Adauga medicament\n");
    printf("2. Modifica medicament\n");
    printf("3. Sterge medicament\n");
    printf("0. Iesire\n");
}

void print_medicamente(Farmacie f)
{
    for (int i = 0; i < get_lungime(&f); i++)
    {
        printf("Cod: %d, Nume: %s, Concentratie: %.2f, Cantitate: %d\n", f.stoc[i].cod, f.stoc[i].nume, f.stoc[i].concentratie, f.stoc[i].cantitate);
    }
}

void run(Farmacie *f)
{
    int ruleaza = 1;
    while (ruleaza)
    {
        print_meniu();
        int cmd;
        scanf("%d", &cmd);
        switch (cmd)
        {
            case 1:
            {
                int cod, cantitate;
                char nume[50];
                float concentratie;
                printf("Introduceti codul: ");
                scanf("%d", &cod);
                printf("Introduceti numele: ");
                scanf("%s", nume, 49);
                printf("Introduceti concentratia: ");
                scanf("%f", &concentratie);
                printf("Introduceti cantitatea disponibila: ");
                scanf("%d", &cantitate);
                Medicament m = creare(cod, nume, concentratie, cantitate);
                if (srv_adaugare(f, cod, nume, concentratie, cantitate))
                {
                    printf("Medicament adaugat!\n");
                }
                else
                {
                    printf("Medicament invalid!\n");
                }
                break;
            }
            case 2:
            {
                int cod, cantitate;
                char nume[50];
                float concentratie;
                printf("Introduceti codul: ");
                scanf("%d", &cod);
                printf("Introduceti numele: ");
                scanf("%s", nume, 49);
                printf("Introduceti concentratia: ");
                scanf("%f", &concentratie);
                if (srv_actualizare(f, cod, nume, concentratie) == 0)
                {
                    printf("Eroare la actualizare!\n");
                }
                else
                {
                    printf("Medicament actualizat!\n");
                }
                break;
            }
            case 3:
            {
                int cod;
                printf("Introduceti codul: ");
                scanf("%d", &cod);
                if (srv_stergere(f, cod) == 0)
                {
                    printf("Eroare la stergere!\n");
                }
                else
                {
                    printf("Medicament sters!\n");
                }
                break;
            }
            case 0:
            {
                ruleaza = 0;
                break;
            }
            default:
            {
                printf("Comanda invalida!\n");
                break;
            }
        }
    }
}