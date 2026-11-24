#include <stdio.h>

int suma(int a, int b, int c);

int main()
{
    int a, b, c;
    printf("a=");
    scanf("%d", &a);
    printf("b=");
    scanf("%d", &b);
    printf("c=");
    scanf("%d", &c);
    int sum = suma(a, b, c);
    printf("Suma este %d", sum);
    return 0;
}