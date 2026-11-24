#include <stdio.h>
#include <stdbool.h>
//Genereaza numere prime mai mici decat un numar natural dat.

bool is_prime(int nr)
{
    /*
    Determina daca un numar natural dat este prim
    params: nr - numar natural
    returns: True/False daca numarul este sau nu prim
    */
    if (nr <= 1)
    {
        return false;
    }
    for (int divi = 2; divi * divi <= nr; divi++)
    {
        if (nr % divi == 0)
        {
            return false;
        }
    }
    return true;
}

void afisare_nr(int nr)
{
    /*
    Afiseaza toate numerele prime mai mici decat numarul natural nr
    params: nr - numar natural, nr > 2
    */
    for (int num = 2; num < nr; num++)
    {
        if (is_prime(num))
        {
            printf("%d ", num);
        }
    }
    printf("\n");
}

int main()
{
    bool run = true;
    while (run)
    {
        printf("1. Afisare numere prime mai mici decat un numar dat\n2. Iesire\nAlegeti o optiune: ");
        int cmd;
        scanf("%d", &cmd);
        switch (cmd)
        {
            case 1:
            {
                int nr;
                printf("Introduceti un numar natural: ");
                scanf("%d", &nr);
                if (nr <= 2)
                {
                    printf("Nu exista numere prime mai mici decat %d!\n", nr);
                }
                else
                {
                    afisare_nr(nr);
                }
                break;
            }
            case 2:
            {
                run = false;
                break;
            }
            default:
            {
                printf("Introduceti o comanda valida!\n");
                if (getchar() != '\n')
                {
                    printf("Comanda invalida!");
                    break;
                }
            }
        }
    }

    return 0;
}