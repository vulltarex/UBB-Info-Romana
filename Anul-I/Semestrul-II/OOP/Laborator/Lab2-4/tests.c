#include "tests.h"
#include "domain.h"
#include "validator.h"
#include "repo.h"
#include "service.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

void teste_domain_validator() {
    Medicament m = creare(1, "Aspirina", 0.5, 100);
    assert(m.cod == 1);
    assert(strcmp(m.nume, "Aspirina") == 0);
    assert(m.concentratie == 0.5);
    assert(m.cantitate == 100);
    assert(validare(m) == 1);
    m.cod = -1;
    assert(validare(m) == 0);
}

void teste_repo() {
    Farmacie f;
    initializare(&f);
    assert(get_lungime(&f) == 0);
    Medicament m = creare(1, "Nurofen", 0.2, 50);
    adaugare(&f, m);
    assert(get_lungime(&f) == 1);
    assert(cautare(&f, 1) == 0);
    stergere(&f, 1);
    assert(get_lungime(&f) == 0);
}

void teste_service() {
    Farmacie f;
    initializare(&f);
    srv_adaugare(&f, 1, "Paracetamol", 0.5, 100);
    assert(get_lungime(&f) == 1);
    srv_adaugare(&f, 1, "Paracetamol", 0.5, 50);
    assert(get_medicament(&f, 0).cantitate == 150);
    srv_actualizare(&f, 1, "Nurofen", 0.2);
    assert(strcmp(get_medicament(&f, 0).nume, "Nurofen") == 0);
    srv_stergere(&f, 1);
    assert(get_lungime(&f) == 0);
}

void test_all() {
    teste_domain_validator();
    teste_repo();
    teste_service();
    printf("Toate testele au trecut!\n");
}