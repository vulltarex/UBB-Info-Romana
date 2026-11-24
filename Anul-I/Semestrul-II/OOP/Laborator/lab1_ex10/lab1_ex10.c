#include <stdio.h>
#include <math.h>
#include <stdbool.h>

/*Tipareste un numar precizat de sume partiale din dezvoltarea
    sin(x) = x - x^3/3! + x^5/5! - x^7/7! + ...
*/

double calcul_termen(double x, int k)
{
    /*
    Calculeaza recursiv al k-1-lea termen al dezvoltari
    params: x - valoare reala aproximata, exprimata in radiani; k - nr termenului -1
    returns: al k-1-lea termen
    */
    if (2 * k + 1 == 1)
    {
        return x;
    }
    else
    {
        return (calcul_termen(x, k - 1) * x * x) / ((2 * k + 1) * (2 * k));
    }
}

double calcul_sin(double x, int k)
{
    /*
    Calculeaza suma (-1)^k * x^(2k+1)/(2k+1)!, k >= 0
    params: x - numar rational, exprima un unghi in radiani, k - nr termeni -1
    returns: x, daca 2k+1 = 1
    */
    if (2*k + 1 == 1)
    {
        return x;
    }
    else
    {
        return pow(-1, k) * calcul_termen(x, k) + calcul_sin(x, k - 1);
    }
}

int main()
{
    bool run = true;
    while (run)
    {
        int cmd;
        printf("1. Afisare sume partiale ale dezvoltarii\n2. Iesire\nAlegeti o optiune: ");
        scanf_s("%d", &cmd);
        switch (cmd)
        {
            case 1:
            {
                int n;
                
                printf("Introduceti numarul de termeni: ");
                scanf_s("%d", &n);
                if (n < 1)
                {
                    printf("Introduceti un numar natural nenul!");
                }
                else
                {
                    double x;
                    printf("Introduceti o valoare pentru x (in grade): ");
                    scanf_s("%lf", &x);
                    //conversie din grade in radiani
                    x = x * 3.1415926535 / 180;
                    for (int k = 0; k < n; k++)
                    {
                        double suma = calcul_sin(x, k);
                        printf("%.15lf  ", suma);
                    }
                    printf("\n");
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
                printf("Introduceti o comanda valida!");
            }
        }
    }
    return 0;
}