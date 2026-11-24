#include "Dictionar.h"
#include <iostream>
#include "IteratorDictionar.h"
#include <cmath>

using namespace std;

int Dictionar::d(TCheie c) const {
	// BC = WC = AC = General = Theta(1)
	return abs(c) % m;
}

void Dictionar::actualizarePrimLiber() {
	// BC = Theta(1), WC = Theta(m), AC = Theta(1)
	primLiber++;
	while (primLiber < m && !liber[primLiber]) {
		primLiber++;
	}
}

void Dictionar::resize() {
	// BC = Theta(m), WC = Theta(m^2), AC = Theta(m)
	int old_m = m;
	m = m * 2;
	TElem* old_e = e;
	int* old_urm = urm;
	bool* old_liber = liber;

	e = new TElem[m];
	urm = new int[m];
	liber = new bool[m];

	for (int i = 0; i < m; i++) {
		urm[i] = -1;
		liber[i] = true;
	}

	size = 0;
	primLiber = 0;

	for (int i = 0; i < old_m; i++) {
		if (!old_liber[i]) {
			adauga(old_e[i].first, old_e[i].second);
		}
	}

	delete[] old_e;
	delete[] old_urm;
	delete[] old_liber;
}

Dictionar::Dictionar() {
	// BC = WC = AC = General = Theta(m)
	m = 10;
	size = 0;
	e = new TElem[m];
	urm = new int[m];
	liber = new bool[m];
	for (int i = 0; i < m; i++) {
		urm[i] = -1;
		liber[i] = true;
	}
	primLiber = 0;
}

Dictionar::~Dictionar() {
	// BC = WC = AC = General = Theta(1)
	delete[] e;
	delete[] urm;
	delete[] liber;
}

TValoare Dictionar::adauga(TCheie c, TValoare v) {
	// BC = Theta(1), WC = Theta(m), AC = Theta(1) amortizat
	int i = d(c);

	if (liber[i]) {
		e[i] = TElem(c, v);
		liber[i] = false;
		urm[i] = -1;
		size++;
		if (i == primLiber) {
			actualizarePrimLiber();
		}
		return NULL_TVALOARE;
	}

	int curent = i;
	int precedent = -1;
	while (curent != -1) {
		if (e[curent].first == c) {
			TValoare veche = e[curent].second;
			e[curent].second = v;
			return veche;
		}
		precedent = curent;
		curent = urm[curent];
	}

	if (size == m) {
		resize();
		return adauga(c, v);
	}

	e[primLiber] = TElem(c, v);
	liber[primLiber] = false;
	urm[primLiber] = -1;
	urm[precedent] = primLiber;
	size++;
	actualizarePrimLiber();

	return NULL_TVALOARE;
}

TValoare Dictionar::cauta(TCheie c) const {
	// BC = Theta(1), WC = Theta(m), AC = Theta(1)
	int i = d(c);
	if (liber[i]) return NULL_TVALOARE;

	int curent = i;
	while (curent != -1) {
		if (e[curent].first == c) {
			return e[curent].second;
		}
		curent = urm[curent];
	}
	return NULL_TVALOARE;
}

TValoare Dictionar::sterge(TCheie c) {
	// BC = Theta(1), WC = Theta(m), AC = Theta(1)
	int i = d(c);
	int ant = -1;
	while (i != -1 && e[i].first != c) {
		ant = i;
		i = urm[i];
	}

	if (i == -1 || liber[i]) return NULL_TVALOARE;

	TValoare veche = e[i].second;
	bool gata = false;

	do {
		int p = urm[i];
		int pp = i;
		while (p != -1) {
			int curent = d(e[p].first);
			bool onPath = false;
			while (curent != -1 && curent != p) {
				if (curent == i) {
					onPath = true;
					break;
				}
				curent = urm[curent];
			}
			if (onPath) {
				break;
			}
			pp = p;
			p = urm[p];
		}

		if (p == -1) {
			gata = true;
		} else {
			e[i] = e[p];
			i = p;
			ant = pp;
		}
	} while (!gata);

	if (ant != -1) {
		urm[ant] = urm[i];
	}
	liber[i] = true;
	urm[i] = -1;
	size--;

	if (i < primLiber) {
		primLiber = i;
	}

	return veche;
}

int Dictionar::dim() const {
	// BC = WC = AC = General = Theta(1)
	return size;
}

bool Dictionar::vid() const {
	// BC = WC = AC = General = Theta(1)
	return size == 0;
}

IteratorDictionar Dictionar::iterator() const {
	// BC = WC = AC = General = Theta(1)
	return IteratorDictionar(*this);
}