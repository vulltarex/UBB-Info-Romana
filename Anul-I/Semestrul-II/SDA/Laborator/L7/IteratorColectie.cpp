#include "IteratorColectie.h"
#include "Colectie.h"
#include <exception>

using namespace std;

IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
	// BC = Theta(1)
	// WC = Theta(n)
	// AC = Theta(log n)
	// General = O(log n)
	capacitateStiva = col.capacitate > 0 ? col.capacitate : 10;
	stiva = new int[capacitateStiva];
	prim();
}

IteratorColectie::~IteratorColectie() {
	// BC = WC = AC = General = Theta(1)
	delete[] stiva;
}

TElem IteratorColectie::element() const{
	// BC = WC = AC = General = Theta(1)
	if (!valid()) {
		throw exception();
	}
	return col.elemente[curent];
}

bool IteratorColectie::valid() const {
	// BC = WC = AC = General = Theta(1)
	return curent != -1;
}

void IteratorColectie::urmator() {
	// BC = Theta(1)
	// WC = Theta(n)
	// AC = Theta(1) amortizat
	// General = Theta(1) amortizat
	if (!valid()) {
		throw exception();
	}

	int nod = stiva[--varf];

	if (col.dr[nod] != -1) {
		nod = col.dr[nod];
		while (nod != -1) {
			stiva[varf++] = nod;
			nod = col.st[nod];
		}
	}

	if (varf > 0) {
		curent = stiva[varf - 1];
	} else {
		curent = -1;
	}
}

void IteratorColectie::prim() {
	// BC = Theta(1)
	// WC = Theta(n)
	// AC = Theta(log n)
	// General = O(log n)
	varf = 0;
	int nod = col.radacina;

	while (nod != -1) {
		stiva[varf++] = nod;
		nod = col.st[nod];
	}

	if (varf > 0) {
		curent = stiva[varf - 1];
	} else {
		curent = -1;
	}
}