#include "IteratorDictionar.h"
#include "Dictionar.h"
#include <exception>

using namespace std;

IteratorDictionar::IteratorDictionar(const Dictionar& d) : dict(d) {
	// BC = Theta(1), WC = Theta(m), AC = Theta(1)
	curent = 0;
	while (curent < dict.m && dict.liber[curent]) {
		curent++;
	}
}

void IteratorDictionar::prim() {
	// BC = Theta(1), WC = Theta(m), AC = Theta(1)
	curent = 0;
	while (curent < dict.m && dict.liber[curent]) {
		curent++;
	}
}

void IteratorDictionar::urmator() {
	// BC = Theta(1), WC = Theta(m), AC = Theta(1)
	if (!valid()) throw exception();
	curent++;
	while (curent < dict.m && dict.liber[curent]) {
		curent++;
	}
}

bool IteratorDictionar::valid() const {
	// BC = WC = AC = General = Theta(1)
	return curent < dict.m;
}

TElem IteratorDictionar::element() const {
	// BC = WC = AC = General = Theta(1)
	if (!valid()) throw exception();
	return dict.e[curent];
}