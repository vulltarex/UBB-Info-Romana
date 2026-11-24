#include <stdio.h>

/*Sa se citeasca un sir de numere intregi s1 (reprezentate pe dublucuvinte) in baza 10. Sa se determine si sa se afiseze sirul s2 compus din cifrele aflate pe poziţia sutelor în fiecare numar intreg din sirul s1.
Exemplu:
Sirul s1: 5892, 456, 33, 7, 245
Sirul s2: 8, 4, 0, 0, 2*/

int cifra_sute(int nr);

int main()
{
    int s1[100], s2[100], n;
    printf("n=");
    scanf("%d", &n);
    printf("Sirul s1:");
    for(int ind = 0; ind < n; ind++)
    {
        scanf("%d", &s1[ind]);
    }
    for(int ind = 0; ind < n; ind++)
    {
        s2[ind] = cifra_sute(s1[ind]);
    }
    printf("\nSirul s2 compus din cifra sutelor fiecarui numar: ");
    for(int ind = 0; ind < n; ind++)
    {
        printf("%d ", s2[ind]);
    }
    return 0;
}