#include "IteratorMultime.h"
#include "Multime.h"


IteratorMultime::IteratorMultime(const Multime& m): mult(m) {
	// BC = WC = AC = Genetal = Theta(1)
	this->prim();
}

TElem IteratorMultime::element() const {
	// BC = WC = AC = Genetal = Theta(1)
	if (valid()) return this->mult.elems[index];
	return -1;
}

bool IteratorMultime::valid() const {
	// BC = WC = AC = Genetal = Theta(1)
	if (this->index >= this->mult.total_size) return false;
	return true;
}

void IteratorMultime::urmator() {
	// BC = WC = AC = Genetal = Theta(1)
	this->index++;
}

void IteratorMultime::prim() {
	// BC = WC = AC = Genetal = Theta(1)
	this->index = 0;
}

