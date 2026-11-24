#include <stdio.h>

/*
Se citeste de la tastatura un numar natural n.
Apoi se citesc n cuvinte de maxim 30 caractere fiecare. Se cere sa se afiseze doar cuvintele, insa afisarea cuvintelor trebuie sa fie facuta dupa rotirea acestora (ex. mere -> erem) 
daca lungimea lor este para, daca nu raman ca in sirul initial.
- main.c - operatiile de citire ciclare si afisare
- modul1.asm - functie care face rotirea unui cuvant + verificarea lungimii
ex.
input:
2
mere
magenta

output:
erem
magenta
*/

int lungime_para(char *cuv);
void rotire(char *cuv);

int main()
{
	int n;
	char cuv[31];

	printf("n=");
	scanf("%d", &n);

	for(int i = 0; i < n; i++)
	{
		scanf("%s", cuv);
		if(lungime_para(cuv))
		{
			rotire(cuv);
		}
		printf("%s\n", cuv);
	}

	return 0;
}