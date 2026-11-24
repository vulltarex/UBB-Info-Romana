#include "tests.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static void tests_domain_validator()
{
	Produs p = creare(1, "laptop", "Apple", "Macbook", 1999.99, 100);
	assert(p.cod == 1);
	assert(strcmp(p.tip, "laptop") == 0);
	assert(strcmp(p.producator, "Apple") == 0);
	assert(strcmp(p.model, "Macbook") == 0);
	assert(p.pret == (float)1999.99);
	assert(p.cantitate == 100);
	Produs other = p;
	assert(egal(p, other) == 1);
	other.cod = 2;
	assert(egal(p, other) == 0);
	assert(validare(p) == 1);
	p.cod = -1;
	assert(validare(p) == 0);
}

static void tests_repo()
{
	Magazin m;
	Produs p = creare(1, "laptop", "Apple", "Macbook", 1999.99, 100);
	m.lungime = 100;
	assert(adaugare(&m, p) == 0);
	initializare(&m);
	assert(get_lungime(&m) == 0);
	adaugare(&m, p);
	assert(get_lungime(&m) == 1);
	assert(cautare(&m, 1) == 0);
	assert(cautare(&m, 2) == -1);
	assert(egal(get_produs(&m, 0), p) == 1);
	p.cantitate = 101;
	actualizare(&m, p);
	assert(m.stoc[0].cantitate == 101);
	p.cod = 2;
	assert(actualizare(&m, p) == 0);
	adaugare(&m, p);
	stergere(&m, 1);
	assert(get_lungime(&m) == 1);
	assert(stergere(&m, 1) == 0);

}

static void tests_service()
{
	Magazin m;
	//adaugare
	initializare(&m);
	assert(srv_adaugare(&m, 0, "laptop", "Apple", "Macbook", 1999.99, 100) == 0);
	srv_adaugare(&m, 1, "laptop", "Apple", "Macbook", 1999.99, 100);
	assert(get_lungime(&m) == 1);
	assert(srv_adaugare(&m, 1, "laptop", "Apple", "Macbook", 999.99, 100) == 0);
	srv_adaugare(&m, 1, "laptop", "Apple", "Macbook", 1999.99, 100);
	assert(get_lungime(&m) == 1);
	assert(m.stoc[0].cantitate == 200);
	//actualizare
	assert(srv_actualizare(&m, 2, 1, 1) == 0);
	assert(srv_actualizare(&m, 1, 0, 0) == 0);
	srv_actualizare(&m, 1, 2000, 100);
	assert(m.stoc[0].pret == 2000 && m.stoc[0].cantitate == 100);
	//stergere
	srv_stergere(&m, 1);
	assert(get_lungime(&m) == 0);
	//sortari
	srv_adaugare(&m, 1, "laptop", "Apple", "Macbook", 1999.99, 100);
	srv_adaugare(&m, 2, "laptop", "Lenovo", "Thinkpad", 999.99, 50);
	Magazin* dto;
	dto = srv_sort_pret(&m, 0);
	assert(egal(dto->stoc[0], m.stoc[1]) == 1);
	free(dto);

	dto = srv_sort_pret(&m, 1);
	assert(egal(dto->stoc[0], m.stoc[0]) == 1);
	free(dto);

	dto = srv_sort_cantitate(&m, 0);
	assert(egal(dto->stoc[0], m.stoc[1]) == 1);
	free(dto);

	dto = srv_sort_cantitate(&m, 1);
	assert(egal(dto->stoc[0], m.stoc[0]) == 1);
	free(dto);

	//filtrari
	dto = srv_filtrare_producator(&m, "Apple");
	assert(get_lungime(dto) == 1);
	free(dto);

	dto = srv_filtrare_pret(&m, 1500, 2500);
	assert(get_lungime(dto) == 1);
	free(dto);
	
	dto = srv_filtrare_pret(&m, 3500, 2500);
	assert(get_lungime(dto) == 0);
	free(dto);

	dto = srv_filtrare_cantitate(&m, 60, 100);
	assert(get_lungime(dto) == 1);
	free(dto);

	dto = srv_filtrare_cantitate(&m, 200, 150);
	assert(get_lungime(dto) == 0);
	free(dto);
}

void test_all()
{
	tests_domain_validator();
	tests_repo();
	tests_service();
	printf("Toate testele au trecut!\n");
}