#include "sortare.h"

void sort(Magazin* m, FunctieComparare cmp_func, int reverse)
{
	for (int i = 0; i < m->lungime; i++)
	{
		for (int j = 0; j < m->lungime - 1; j++)
		{
			Produs p1 = get_elem(m, j);
			Produs p2 = get_elem(m, j + 1);
			if (reverse == 0 && cmp_func(&p1, &p2) > 0 || reverse == 1 && cmp_func(&p1, &p2) < 0)
			{
				set_elem(m, p2, j);
				set_elem(m, p1, j + 1);
			}
			else
			{
				destroy_produs(&p1);
				destroy_produs(&p2);
			}
		}
	}
}