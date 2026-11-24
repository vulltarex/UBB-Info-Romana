#pragma once

typedef struct {
	int cod, cantitate;
	char *tip, *producator, *model;
	float pret;
}Produs;

/*
Construieste o entitate Produs.
Pre: cod (intreg > 0), tip, producator, model (siruri nevide), pret (real > 0), cantitate (intreg > 0).
Post: Returneaza entitatea Produs. Sirurile > 49 caractere sunt trunchiate.
*/
Produs creare(int cod, const char* tip, const char* producator, const char* model, float pret, int cantitate);
/*
Evalueaza echivalenta a doua produse ignorand cantitatea disponibila.
Pre: p, other - entitati Produs initializate.
Post: Returneaza 1 daca cod, tip, producator, model si pret sunt identice. 0 altfel.
*/
int egal(Produs p, Produs other);

/*
Elibereaza memoria alocata sirurilor de caractere, nulifica adresele de memorie ale pointerilor si invalideaza atributele numerice.
Pre: p - pointer catre un produs initializat
Post: memoria alocata stocarii informatiilor despre produs este eliberata, atributele si pointerii sunt distrusi
*/
void destroy_produs(Produs* p);

/*
Returneaza o copie a unui produs
Pre: p - pointer catre un produs initializat
Post: este returnata o alta entitate Produs care are atributele identice cu cele ale produsului transmis ca parametru
*/
Produs copy_produs(Produs* p);