#include "ui.h"
#include <stdio.h>

static void print_meniu()
{
	printf("1. Adaugare produs\n");
	printf("2. Actualizare produs\n");
	printf("3. Stergere produs\n");
	printf("4. Vizualizare produse\n");
	printf("5. Filtrare produse\n");
	printf("0. Iesire\n");
}

static void print_meniu_sort()
{
	printf("1. Sortare dupa pret\n");
	printf("2. Sortare dupa cantitate disponibila\n");
}

static void print_meniu_ordine()
{
	printf("0. Crescator\n");
	printf("1. Descrescator\n");
}

static void print_meniu_filtrare()
{
	printf("1. Filtrare dupa producator\n");
	printf("2. Filtrare dupa pret\n");
	printf("3. Filtrare dupa cantitate\n");
}

static void afisare_produse(Magazin* m)
{
	for (int i = 0; i < get_lungime(m); i++)
	{
		Produs p = get_produs(m, i);
		printf("Cod: %d, tip: %s, producator: %s, model: %s, pret: %.2f RON, cantitate: %d\n", p.cod, p.tip, p.producator, p.model, p.pret, p.cantitate);
	}
}

static int citire_int(const char* comanda)
{
	while(1)
	{
		int val;
		printf("%s", comanda);
		if (scanf_s("%d", &val) == 1)
		{
			return val;
		}
		printf("Introduceti un numar intreg!\n");
		while (getchar() != '\n');
	}
}

static float citire_float(const char* comanda)
{
	while(1)
	{
		float val;
		printf("%s", comanda);
		if (scanf_s("%f", &val) == 1)
		{
			return val;
		}
		printf("Introduceti un numar!\n");
		while (getchar() != '\n');
	}
}

void run(Magazin* m)
{
	int ruleaza = 1;
	while (ruleaza)
	{
		print_meniu();
		int cmd = citire_int("Introduceti o comanda: ");
		switch (cmd)
		{
			case 1:
			{
				int cod, cantitate;
				char tip[50], producator[50], model[50];
				float pret;
				cod = citire_int("Introduceti codul produsului: ");
				printf("Introduceti tipul produsului: ");
				scanf_s(" %[^\n]", tip, 49);
				printf("Introduceti producatorul produsului: ");
				scanf_s(" %[^\n]", producator, 49);
				printf("Introduceti modelul produsului: ");
				scanf_s(" %[^\n]", model, 49);
				pret = citire_float("Introduceti pretul produsului: ");
				cantitate = citire_int("Introduceti cantitatea disponibila: ");
				if (srv_adaugare(m, cod, tip, producator, model, pret, cantitate) == 1)
				{
					printf("Produs adaugat!\n");
				}
				else
				{
					printf("Eroare la adaugare!\n");
				}
				break;
			}
			case 2:
			{
				int cod, cantitate;
				float pret;
				cod = citire_int("Introduceti codul produsului: ");
				pret = citire_float("Introduceti pretul produsului: ");
				cantitate = citire_int("Introduceti cantitatea disponibila: ");
				if (srv_actualizare(m, cod, pret, cantitate) == 1)
				{
					printf("Produs actualizat!\n");
				}
				else
				{
					printf("Eroare la actualizare!\n");
				}
				break;
			}
			case 3:
			{
				int cod;
				cod = citire_int("Introduceti codul produsului: ");
				if (srv_stergere(m, cod) == 1)
				{
					printf("Produs sters!\n");
				}
				else
				{
					printf("Eroare la stergere!\n");
				}
				break;
			}
			case 4:
			{
				int option;
				print_meniu_sort();
				option = citire_int("Alegeti o optiune: ");

				switch (option)
				{
					case 1:
					{
						int reverse;
						do
						{
							print_meniu_ordine();
							reverse = citire_int("Alegeti o optiune: ");
							if (reverse != 0 && reverse != 1)
							{
								printf("Comanda invalida!\n");
							}
						} while (reverse != 0 && reverse != 1);
						Magazin* rez = srv_sort_pret(m, reverse);
						afisare_produse(rez);
						free(rez);
						break;
					}
					case 2:
					{
						int reverse;
						do
						{
							print_meniu_ordine();
							reverse = citire_int("Alegeti o optiune: ");
							if (reverse != 0 && reverse != 1)
							{
								printf("Comanda invalida!\n");
							}
						} while (reverse != 0 && reverse != 1);
						Magazin* rez = srv_sort_cantitate(m, reverse);
						afisare_produse(rez);
						free(rez);
						break;
					}
					default:
					{
						printf("Comanda invalida!\n");
						break;
					}
				}
				break;
			}
			case 5:
			{
				print_meniu_filtrare();
				int option;
				option = citire_int("Alegeti o optiune: ");
				switch (option)
				{
					case 1:
					{
						char producator[50];
						printf("Introduceti producatorul: ");
						scanf_s(" %[^\n]", producator, 49);
						Magazin* rez = srv_filtrare_producator(m, producator);
						afisare_produse(rez);
						free(rez);
						break;
					}
					case 2:
					{
						float pret_min, pret_max;
						pret_min = citire_float("Introduceti pretul minim: ");
						pret_max = citire_float("Introduceti pretul maxim: ");
						if (pret_min > pret_max)
						{
							float aux = pret_min;
							pret_min = pret_max;
							pret_max = aux;
						}
						Magazin* rez = srv_filtrare_pret(m, pret_min, pret_max);
						afisare_produse(rez);
						free(rez);
						break;
					}
					case 3:
					{
						int cant_min, cant_max;
						cant_min = citire_int("Introduceti cantitatea minima: ");
						cant_max = citire_int("Introduceti cantitatea maxima: ");
						if (cant_min > cant_max)
						{
							int aux = cant_min;
							cant_min = cant_max;
							cant_max = aux;
						}
						Magazin* rez = srv_filtrare_cantitate(m, cant_min, cant_max);
						afisare_produse(rez);
						free(rez);
						break;
					}
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
				printf("Introduceti o comanda valida!\n");
			}
		}
	}
}