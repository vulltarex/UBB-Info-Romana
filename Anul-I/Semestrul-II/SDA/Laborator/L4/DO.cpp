#include "Iterator.h"
#include "DO.h"
#include <iostream>

#include <exception>
using namespace std;

void DO::resize() {
	// WC = BC = AC = General = Theta(n);
	this->capacity *= 2;
	TElem* new_e = new TElem[this->capacity]();
	int* new_urm = new int[this->capacity]();
	int* new_prec = new int[this->capacity]();

	for (int i = 0; i < this->capacity / 2; i++) {
		new_e[i] = this->e[i];
		new_urm[i] = this->urm[i];
		new_prec[i] = this->prec[i];
	}

	delete[] e;
	delete[] urm;
	delete[] prec;
	this->e = new_e;
	this->urm = new_urm;
	this->prec = new_prec;
}

int DO::poz_prim_liber() {
	// BC = Theta(1)
	// WC = Theta(n)
	// AC = Theta(n)
	// General = O(n)
	for (int i = 0; i < this->capacity; i++) {
		if (urm[i] == 0 && prec[i] == 0) {
			return i;
		}
	}
	return -1;
}

DO::DO(Relatie r) {
	// WC = BC = AC = General = Theta(1);
	this->r = r;
	this->e = new TElem[10];
	this->urm = new int[10]();
	this->prec = new int[10]();
	this->prim = this->ultim = -1;
	this->size = 0;
	this->capacity = 10;
	this->prim_liber = 0;
}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga(TCheie c, TValoare v) {
	// BC = Theta(1)
	// WC = Theta(n)
	// AC = Theta(n)
	// General = O(n)
	if (vid()) {
		this->e[0] = TElem(c,v);
		this->urm[0] = this->prec[0] = -1;
		this->prim = this->ultim = 0;
		this->prim_liber = 1;
		this->size++;
		return NULL_TVALOARE;
	}
	if (cauta(c) != NULL_TVALOARE) {
		int i;
		for (i = this->prim; this->e[i].first != c; i = this->urm[i]);
		TValoare val = this->e[i].second;
		this->e[i].second = v;
		return val;
	}
	if (this->size == this->capacity) {
		resize();
		this->prim_liber = poz_prim_liber();
	}
	if (r(c, this->e[prim].first)) {
		e[prim_liber] = TElem(c, v);
		urm[prim_liber] = prim;
		prec[prim_liber] = -1;
		prec[prim] = prim_liber;
		prim = prim_liber;
		prim_liber = poz_prim_liber();
		this->size++;
		return NULL_TVALOARE;
	}
	if (!r(c,this->e[ultim].first)) {
		e[prim_liber] = TElem(c, v);
		urm[prim_liber] = -1;
		prec[prim_liber] = ultim;
		urm[ultim] = prim_liber;
		ultim = prim_liber;
		prim_liber = poz_prim_liber();
		this->size++;
		return NULL_TVALOARE;
	}
	int i;
	for (i = this->prim; urm[i] != -1 && !r(c, e[urm[i]].first); i=urm[i]);
	e[prim_liber] = TElem(c, v);
	urm[prim_liber] = urm[i];
	prec[prim_liber] = i;
	if (urm[i] != -1) {
		prec[urm[i]] = prim_liber;
	}
	else {
		this->ultim = prim_liber;
	}
	urm[i] = prim_liber;
	prim_liber = poz_prim_liber();
	size++;
	return NULL_TVALOARE;
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const {
	// BC = Theta(1)
	// WC = Theta(n)
	// AC = Theta(n)
	// General = O(n)
	if (vid()) return NULL_TVALOARE;
	for (int i = this->prim; i != -1; i = this->urm[i]) {
		if (e[i].first == c) {
			return e[i].second;
		}
	}
	return NULL_TVALOARE;	
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) {
	// BC = Theta(1)
	// WC = Theta(n)
	// AC = Theta(n)
	// General = O(n)
	int i;
	for (i = this->prim; i != -1 && e[i].first != c; i = urm[i]);

	if (i == -1) {
		return NULL_TVALOARE;
	}

	if (this->size == 1) {
		urm[prim] = prec[prim] = 0;
		TValoare val = e[prim].second;
		this->prim = this->ultim = -1;
		this->size--;
		return val;
	}
	if (i == this->prim) {
		TValoare val = e[i].second;
		prec[urm[i]] = -1;
		this->prim = urm[i];
		urm[i] = prec[i] = 0;
		e[i].first = NULL_TVALOARE;
		e[i].second = NULL_TVALOARE;
		this->size--;
		return val;
	}
	if (i == this->ultim) {
		TValoare val = e[i].second;
		urm[prec[i]] = -1;
		this->ultim = prec[i];
		urm[i] = prec[i] = 0;
		e[i].first = NULL_TVALOARE;
		e[i].second = NULL_TVALOARE;
		this->size--;
		return val;
	}
	TValoare val = e[i].second;
	urm[prec[i]] = urm[i];
	prec[urm[i]] = prec[i];
	urm[i] = prec[i] = 0;
	e[i].first = NULL_TVALOARE;
	e[i].second = NULL_TVALOARE;
	this->size--;
	return val;
}

//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const {
	// WC = BC = AC = General = Theta(1);
	return this->size;
}

//verifica daca dictionarul e vid
bool DO::vid() const {
	// WC = BC = AC = General = Theta(1);
	return this->size == 0;
}

Iterator DO::iterator() const {
	// WC = BC = AC = General = Theta(1);
	return  Iterator(*this);
}

DO::~DO() {
	// WC = BC = AC = General = Theta(1);
	delete[] e;
	delete[] urm;
	delete[] prec;
}
