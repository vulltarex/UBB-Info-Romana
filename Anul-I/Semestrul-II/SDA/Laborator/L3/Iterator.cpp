#include "Iterator.h"

#include <exception>

#include "LO.h"

Iterator::Iterator(const LO& lo) : lista(lo){
	// BC = WC = AC = Theta(1)
	prim();
}

void Iterator::prim() {
	// BC = WC = AC = Theta(1)
	this->curent = this->lista.first;
}

void Iterator::urmator(){
	// BC = WC = AC = Theta(1)
	if (!valid()) throw std::exception();
	this->curent = this->curent->next;
}

bool Iterator::valid() const{
	// BC = WC = AC = Theta(1)
	return this->curent != nullptr;
}

TElement Iterator::element() const{
	// BC = WC = AC = Theta(1)
	if (!valid()) throw std::exception();
	return this->curent->value;
}