#include <stdio.h>

/*
Se citeste o propozitie de la tastatura. Sa se inverseze fiecare cuvant
si sa se afiseze pe ecran.
*/

void procesare(char *sir);

int main()
{
	char sir[255];
	gets(sir);
	procesare(sir);
	printf("%s", sir);

	return 0;
}
/*while (s[i] != 0)
{
	cnt = 0;
	int start = i;
	while (s[i] != ' ')
	{
		cnt++;
		i++;
	}
	while (start < cnt / 2)
	{
		swap(s[start], s[cnt - start - 1]);
		start++
	}
	
	i++;
}*/
//ana are mere0
//0123456789012
//   