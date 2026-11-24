#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>

using namespace std;

bool rel(TElem e1, TElem e2) {
	// BC = WC = AC = General = Theta(1)
	return e1 <= e2;
}

int Colectie::aloca() {
	// BC = WC = AC = General = Theta(1)
	int i = primLiber;
	primLiber = st[primLiber];
	return i;
}

void Colectie::dealoca(int i) {
	// BC = WC = AC = General = Theta(1)
	st[i] = primLiber;
	primLiber = i;
}

void Colectie::redim() {
	// BC = WC = AC = General = Theta(c)
	TElem* elementeNou = new TElem[capacitate * 2];
	int* stNou = new int[capacitate * 2];
	int* drNou = new int[capacitate * 2];

	for (int i = 0; i < capacitate; i++) {
		elementeNou[i] = elemente[i];
		stNou[i] = st[i];
		drNou[i] = dr[i];
	}

	for (int i = capacitate; i < capacitate * 2 - 1; i++) {
		stNou[i] = i + 1;
	}
	stNou[capacitate * 2 - 1] = -1;
	primLiber = capacitate;

	delete[] elemente;
	delete[] st;
	delete[] dr;

	elemente = elementeNou;
	st = stNou;
	dr = drNou;
	capacitate *= 2;
}

Colectie::Colectie() {
	// BC = WC = AC = General = Theta(c)
	capacitate = 10;
	dimensiune = 0;
	radacina = -1;
	primLiber = 0;

	elemente = new TElem[capacitate];
	st = new int[capacitate];
	dr = new int[capacitate];

	for (int i = 0; i < capacitate - 1; i++) {
		st[i] = i + 1;
	}
	st[capacitate - 1] = -1;
}

void Colectie::adauga(TElem e) {
	// BC = Theta(1)
	// WC = Theta(n)
	// AC = Theta(log n)
	// General = O(log n)
	if (primLiber == -1) {
		redim();
	}

	int nou = aloca();
	elemente[nou] = e;
	st[nou] = -1;
	dr[nou] = -1;

	if (radacina == -1) {
		radacina = nou;
	}
	else {
		int curent = radacina;
		int parinte = -1;

		while (curent != -1) {
			parinte = curent;
			if (rel(e, elemente[curent])) {
				curent = st[curent];
			} else {
				curent = dr[curent];
			}
		}

		if (rel(e, elemente[parinte])) {
			st[parinte] = nou;
		} else {
			dr[parinte] = nou;
		}
	}
	dimensiune++;
}


bool Colectie::sterge(TElem e) {
	// BC = Theta(1)
	// WC = Theta(n)
	// AC = Theta(log n)
	// General = O(log n)
	int curent = radacina;
	int parinte = -1;
	bool gasit = false;

	while (curent != -1 && !gasit) {
		if (elemente[curent] == e) {
			gasit = true;
		} else {
			parinte = curent;
			if (rel(e, elemente[curent])) {
				curent = st[curent];
			} else {
				curent = dr[curent];
			}
		}
	}

	if (!gasit) return false;

	if (st[curent] != -1 && dr[curent] != -1) {
		int predecesor = st[curent];
		int parintePredecesor = curent;

		while (dr[predecesor] != -1) {
			parintePredecesor = predecesor;
			predecesor = dr[predecesor];
		}

		elemente[curent] = elemente[predecesor];
		curent = predecesor;
		parinte = parintePredecesor;
	}

	int fiu = (st[curent] != -1) ? st[curent] : dr[curent];

	if (parinte == -1) {
		radacina = fiu;
	} else {
		if (st[parinte] == curent) {
			st[parinte] = fiu;
		} else {
			dr[parinte] = fiu;
		}
	}

	dealoca(curent);
	dimensiune--;
	return true;
}


bool Colectie::cauta(TElem elem) const {
	// BC = Theta(1)
	// WC = Theta(n)
	// AC = Theta(log n)
	// General = O(log n)
	int curent = radacina;
	while (curent != -1) {
		if (elemente[curent] == elem) {
			return true;
		}
		if (rel(elem, elemente[curent])) {
			curent = st[curent];
		} else {
			curent = dr[curent];
		}
	}
	return false;
}


int Colectie::nrAparitii(TElem elem) const {
	// BC = WC = AC = General = Theta(log n)
	int contor = 0;
	int curent = radacina;
	while (curent != -1) {
		if (elemente[curent] == elem) {
			contor++;
		}
		if (rel(elem, elemente[curent])) {
			curent = st[curent];
		} else {
			curent = dr[curent];
		}
	}
	return contor;
}

int Colectie::dim() const {
	// BC = WC = AC = General = Theta(1)
	return dimensiune;
}

bool Colectie::vida() const {
	// BC = WC = AC = General = Theta(1)
	return dimensiune == 0;
}

IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}

Colectie::~Colectie() {
	// BC = WC = AC = General = Theta(1)
	delete[] elemente;
	delete[] st;
	delete[] dr;
}