#include "validator.h"
#include <string.h>

int validare(Produs p)
{
	/*
	Evalueaza integritatea campurilor unei structuri Produs conform regulilor de domeniu.
	Preconditii:
	- p: structura Produs.
	Postconditii:
	- Returneaza 1 daca toate regulile sunt respectate: cod > 0, pret > 0, cantitate > 0, iar sirurile tip, producator si model sunt nevide.
	- Returneaza 0 la prima incalcare validata.
	*/
	if (p.cod <= 0) return 0;
	if (strlen(p.tip) == 0) return 0;
	if (strlen(p.producator) == 0) return 0;
	if (strlen(p.model) == 0) return 0;
	if (p.pret <= 0) return 0;
	if (p.cantitate <= 0) return 0;
	return 1;
}