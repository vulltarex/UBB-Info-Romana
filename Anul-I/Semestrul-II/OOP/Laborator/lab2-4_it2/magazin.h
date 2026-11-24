#pragma once
#include "domain.h"

typedef struct
{
	Produs* stoc;
	int lungime;
	int capacitate;
}Magazin;

/*
Aloca dinamic si initializeaza un vector pentru stocarea produselor.
Pre: -
Post: Returneaza o instanta Magazin cu capacitate initiala 2 si lungime 0.
*/
Magazin create_empty();

/*
Insereaza o entitate la sfarsitul vectorului. Realizeaza redimensionare automata la atingerea capacitatii.
Pre: m - pointer valid la Magazin, p - entiate Produs validata.
Post: Lungimea logica creste cu 1, p este adaugat.
*/
void add(Magazin* m, Produs p);

/*
Furnizeaza numarul curent de elemente din vector.
Pre: m - pointer valid la Magazin.
Post: Returneaza lungimea (intreg >= 0).
*/
int size(const Magazin* m);

/*
Elimina elementul de la indexul specificat.
Pre: m - pointer valid la Magazin. 0 <= index < size(m).
Post: Lungimea scade cu 1, pastrand ordinea elementelor ramase.
*/
void remove_elem(Magazin* m, int index);

/*
Dubleaza capacitatea de stocare a vectorului dinamic alocat.
Pre: m - pointer valid la o instanta Magazin.
Post: Capacitatea este dublata, elementele existente sunt copiate, vechiul bloc de memorie este eliberat.
*/
void resize(Magazin* m);

/*
Elibereaza memoria alocata pentru tabloul intern si reseteaza contoarele.
Pre: m - pointer valid la Magazin creat anterior cu create_empty().
Post: m->stoc este dealocat, capacitatea si lungimea devin 0.
*/
void destroy(Magazin* m);

/*
Suprascrie valoarea stocata la indexul specificat cu o noua entitate.
Pre: m - pointer valid la Magazin. p - entitate Produs. 0 <= index < size(m).
Post: Elementul de la index capata valoarea p.
*/
void set_elem(Magazin* m, Produs p, int index);

/*
Returneaza o copie a elementului de la indexul specificat.
Pre: m - pointer valid la Magazin. 0 <= index < size(m).
Post: Returneaza entitatea Produs stocata la pozitia respectiva.
*/
Produs get_elem(const Magazin* m, int index);