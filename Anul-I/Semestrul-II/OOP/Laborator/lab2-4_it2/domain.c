#include "domain.h"
#include <string.h>
#include <stdlib.h>

Produs creare(int cod, const char* tip, const char* producator, const char* model, float pret, int cantitate)
{
	Produs p;
	p.cod = cod;
	p.tip = (char*)malloc(strlen(tip) + 1);
	p.producator = (char*)malloc(strlen(producator) + 1);
	p.model = (char*)malloc(strlen(model) + 1);
	if (p.tip) strcpy_s(p.tip, strlen(tip) + 1, tip);
	if (p.producator) strcpy_s(p.producator, strlen(producator) + 1, producator);
	if (p.model) strcpy_s(p.model, strlen(model) + 1, model);
	p.pret = pret;
	p.cantitate = cantitate;

	return p;
}

int egal(Produs p, Produs other)
{
	if (p.cod != other.cod) return 0;
	if (strcmp(p.tip, other.tip) != 0) return 0;
	if (strcmp(p.producator, other.producator) != 0) return 0;
	if (strcmp(p.model, other.model) != 0) return 0;
	if (p.pret != other.pret) return 0;
	return 1;
}

void destroy_produs(Produs* p)
{
	free(p->tip);
	free(p->producator);
	free(p->model);

	p->tip = NULL;
	p->producator = NULL;
	p->model = NULL;

	p->cod = -1;
	p->pret = -1;
	p->cantitate = -1;
}

Produs copy_produs(Produs* p)
{
	return creare(p->cod, p->tip, p->producator, p->model, p->pret, p->cantitate);
}
