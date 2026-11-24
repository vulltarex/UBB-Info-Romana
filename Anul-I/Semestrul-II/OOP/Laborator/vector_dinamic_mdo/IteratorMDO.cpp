#include "IteratorMDO.h"
#include "MDO.h"

IteratorMDO::IteratorMDO(const MDO& d) : dict(d){
	// BC = WC = AC = General = Theta(m)
	this->prim();
}

void IteratorMDO::prim(){
	// BC = WC = AC = General = Theta(m)
	this->outer_index = 0;
	this->inner_index = 0;
	if (this->outer_index < this->dict.used_capacity) {
		this->cached_values = this->dict.elements[this->outer_index]->get_all();
	}
}

void IteratorMDO::urmator(){
	// BC = Theta(1)
	// WC = Theta(m)
	// AC = Theta(1)
	// General = Theta(1) amortizat

	this->inner_index++;
	if (this->inner_index < this->cached_values.size()) {
		return;
	}
	this->outer_index++;
	this->inner_index = 0;
	if (this->outer_index < this->dict.used_capacity) {
		this->cached_values = this->dict.elements[this->outer_index]->get_all();
	}
}

bool IteratorMDO::valid() const{
	// BC = WC = AC = General = Theta(1)
	return this->outer_index < this->dict.used_capacity;
}

TElem IteratorMDO::element() const{
	// BC = WC = AC = General = Theta(1)
	return pair <TCheie, TValoare>(
		this->dict.elements[this->outer_index]->get_key(),
		this->cached_values[this->inner_index]
	);
}


