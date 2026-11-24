#include "Iterator.h"

#include <exception>

#include "DO.h"

using namespace std;

Iterator::Iterator(const DO& d) : dict(d){
	// BC = WC = AC = General = Theta(1)
	this->curent = d.prim;
}

void Iterator::prim(){
	// BC = WC = AC = General = Theta(1)
	this->curent = this->dict.prim;
}

void Iterator::urmator() {
	// BC = WC = AC = General = Theta(1)
	if (!valid()) throw exception();
	this->curent = this->dict.urm[curent];
}

bool Iterator::valid() const{
	// BC = WC = AC = General = Theta(1)
	return this->curent != -1;
}

TElem Iterator::element() const{
	// BC = WC = AC = General = Theta(1)
	if (!valid()) throw exception();
	return dict.e[curent];
}


