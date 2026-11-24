#include <stdio.h>
#include <stdbool.h>

/*Tipareste un numar precizat de termeni din sirul 1, 2,1, 3,2,1, 4,2,2, 5,4,3,2,1, 6,2,2,3,3,3, 7,6, ... 
obtinut din sirul numerelor naturale prin inlocuirea fiecarui numar natural n printr-un grup de numere. Numarul
prim p este inlocuit prin numerele p,p-1,...3,2,1, iar numarul compus n este inlocuit prin n urmat de toti divizorii sai proprii,
un divizor d repetandu-se de d ori.*/

bool is_prime(int nr)
{
	/*
	Verifica daca un numar natural dat este prim
	params: nr - un numar natural
	returns: true/false daca numarul este sau nu prim nr
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

void generare_termeni(int n)
{
	/*
	Genereaza si afiseaza primii n termeni ai sirului dat
	params: n - numar natural nenul
	*/
	int cnt = 0, nr = 1;
	while (true)
	{
		int termen = nr;
		if (is_prime(nr))
		{
			while (termen != 0 && cnt < n)
			{
				printf("%d ", termen--);
				cnt++;
			}
			if (termen != 0)
			{
				break;
			}
		}
		else
		{
			printf("%d ", termen);
			if (++cnt == n)
			{
				break;
			}
			int divi = 2;
			while (divi <= termen / 2 && cnt < n)
			{
				if (termen % divi == 0)
				{
					for (int ind = 1; ind <= divi && cnt < n; ind++)
					{
						printf("%d ", divi);
						cnt++;
					}
				}
				divi++;
			}
			if (cnt == n)
			{
				break;
			}
		}
		nr++;
	}
	printf("\n");
}

int main()
{
	bool run = true;
	while (run)
	{
		printf("1. Tiparire termeni\n2. Iesire\nAlegeti o optiune: ");
		int cmd;
		scanf_s("%d", &cmd);
		switch (cmd)
		{
			case 1:
			{
				int n;
				printf("Introduceti un numar natural: ");
				scanf_s("%d", &n);
				if (n < 1)
				{
					printf("Numar invalid!\n");
				}
				else
				{
					generare_termeni(n);
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
				printf("Comanda invalida!\n");
			}
		}
	}
	return 0;
}