/*
citeste de la tastatura un N (0<n<9)
apoi citeste numere hexa pana la introd lui 0

progr va afisa nr citit si suma cifrelor sale hexa
doar daca e pozitiv sivformat din cel putin n cifre
hexa iar la final va afisa suma cifrelor tuturor 
cifrelor care au indeplinit conditiile date

doua proceduri:
-verifica_numar care verif daca numarul 
indeplineste conditiile si returneaza suma cifrelor
-afisare_suma care afiseaza suma ceruta
*/

#include <stdio.h>

int verifica_numar(int numar, int n);
void afisare_suma(int suma);

int main()
{
	int n = 0, nr = 1, suma = 0, verif;
	printf("n = ");
	scanf("%d", &n);
	getchar();
	
	while (nr != 0)
	{
		printf("numar: ");
		scanf("%x", &nr);
		getchar();
		if (nr != 0) 
		{
			verif = verifica_numar(nr, n);
			if (verif != 0)
			{
				printf("%x %d", nr, verif);
				suma += verif;
			}
		}
	}
	afisare_suma(suma);
}
