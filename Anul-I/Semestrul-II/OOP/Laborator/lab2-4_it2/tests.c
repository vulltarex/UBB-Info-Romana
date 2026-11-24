#include "tests.h"
#include "validator.h"
#include "repo.h"
#include "service.h"
#include "domain.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void tests_domain_validator()
{
	Produs p = creare(1, "laptop", "Apple", "Macbook", (float)1999.99, 100);
	assert(p.cod == 1);
	assert(strcmp(p.tip, "laptop") == 0);
	assert(strcmp(p.producator, "Apple") == 0);
	assert(strcmp(p.model, "Macbook") == 0);
	assert(p.pret == (float)1999.99);
	assert(p.cantitate == 100);
	Produs other = copy_produs(&p);
	assert(egal(p, other) == 1);
	other.cod = 2;
	assert(egal(p, other) == 0);
	assert(validare(p) == 1);
	p.cod = -1;
	assert(validare(p) == 0);
	destroy_produs(&p);
	destroy_produs(&other);
}

static void tests_magazin()
{
	Magazin m = create_empty();
	//initializare
	assert(m.lungime == 0);
	assert(m.capacitate == 2);
	assert(m.stoc != NULL);
	//adaugare si redimensionare
	Produs p1 = creare(1, "laptop", "Apple", "Macbook", (float)1999.99, 100);
	Produs p2 = creare(2, "laptop", "Asus", "ROG", (float)2999.99, 50);
	Produs p3 = creare(3, "laptop", "Lenovo", "ThinkPad", (float)1599.99, 75);

	add(&m, p1);
	add(&m, p2);
	add(&m, p3);
	assert(m.capacitate == 4);
	assert(size(&m) == 3);

	Produs temp = get_elem(&m, 0);
	assert(temp.cod == 1);
	destroy_produs(&temp);

	remove_elem(&m, 0);
	assert(size(&m) == 2);

	Produs p_nou = creare(4, "telefon", "Samsung", "Galaxy S26", (float)3500, 50);
	set_elem(&m, p_nou, 0);

	temp = get_elem(&m, 0);
	assert(temp.cod == 4);
	destroy_produs(&temp);

	destroy(&m);
	assert(m.lungime == 0);
	assert(m.capacitate == 0);
}

static void tests_repo()
{
	Magazin m;
	initializare(&m);
	assert(get_lungime(&m) == 0);

	Produs p1 = creare(1, "laptop", "Apple", "Macbook", (float)1999.99, 100);
	adaugare(&m, p1);

	assert(get_lungime(&m) == 1);
	assert(cautare(&m, 1) == 0);
	assert(cautare(&m, 2) == -1);

	Produs temp = get_produs(&m, 0);
	assert(egal(temp, p1) == 1);
	destroy_produs(&temp);

	Produs p_nou = creare(1, "laptop", "Apple", "Macbook", (float)1999.99, 101);
	actualizare(&m, p_nou);
	assert(m.stoc[0].cantitate == 101);
	
	Produs p2 = creare(2, "laptop", "Lenovo", "ThinkPad", (float)999.99, 50);;
	assert(actualizare(&m, p2) == 0);

	adaugare(&m, p2);
	assert(get_lungime(&m) == 2);

	stergere(&m, 1);
	assert(get_lungime(&m) == 1);
	assert(stergere(&m, 1) == 0);

	destroy(&m);
}

static void tests_service()
{
	Magazin m;
	//adaugare
	initializare(&m);
	assert(srv_adaugare(&m, 0, "laptop", "Apple", "Macbook", (float)1999.99, 100) == 0);

	srv_adaugare(&m, 1, "laptop", "Apple", "Macbook", (float)1999.99, 100);
	assert(get_lungime(&m) == 1);

	assert(srv_adaugare(&m, 1, "laptop", "Apple", "Macbook", (float)999.99, 100) == 0);
	srv_adaugare(&m, 1, "laptop", "Apple", "Macbook", (float)1999.99, 100);
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
	Produs p1 = creare(1, "laptop", "Apple", "Macbook", (float)1999.99, 100);
	Produs p2 = creare(1, "laptop", "Apple", "Macbook", (float)1999.99, 100);
	assert(cmp_cantitate(&p1, &p2) == 0);
	assert(cmp_pret(&p1, &p2) == 0);
	destroy_produs(&p1);
	destroy_produs(&p2);

	srv_adaugare(&m, 1, "laptop", "Apple", "Macbook", (float)1999.99, 100);
	srv_adaugare(&m, 2, "laptop", "Lenovo", "Thinkpad", (float)999.99, 50);
	Magazin* dto;
	dto = srv_sort_pret(&m, 0);
	assert(egal(dto->stoc[0], m.stoc[1]) == 1);
	destroy(dto);
	free(dto);

	dto = srv_sort_pret(&m, 1);
	assert(egal(dto->stoc[0], m.stoc[0]) == 1);
	destroy(dto);
	free(dto);

	dto = srv_sort_cantitate(&m, 0);
	assert(egal(dto->stoc[0], m.stoc[1]) == 1);
	destroy(dto);
	free(dto);

	dto = srv_sort_cantitate(&m, 1);
	assert(egal(dto->stoc[0], m.stoc[0]) == 1);
	destroy(dto);
	free(dto);

	//filtrari
	dto = srv_filtrare_producator(&m, "Apple");
	assert(get_lungime(dto) == 1);
	destroy(dto);
	free(dto);

	dto = srv_filtrare_pret(&m, 1500, 2500);
	assert(get_lungime(dto) == 1);
	destroy(dto);
	free(dto);

	dto = srv_filtrare_pret(&m, 3500, 2500);
	assert(get_lungime(dto) == 0);
	destroy(dto);
	free(dto);

	dto = srv_filtrare_cantitate(&m, 60, 100);
	assert(get_lungime(dto) == 1);
	destroy(dto);
	free(dto);

	dto = srv_filtrare_cantitate(&m, 200, 150);
	assert(get_lungime(dto) == 0);
	destroy(dto);
	free(dto);

	destroy(&m);
}

void test_all()
{
	tests_domain_validator();
	tests_magazin();
	tests_repo();
	tests_service();
	printf("Toate testele au trecut!\n");
}