#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>

using namespace std;

bool rel(TElem e1, TElem e2) {
	// BC = WC = AC = Genetal = Theta(1)
	return e1 <= e2;
}

Multime::Multime() {
	// BC = WC = AC = Genetal = Theta(1)
	this->relation = rel;
	this->total_size = 0;
	this->capacity = 10;
	this->elems = new TElem[this->capacity];
}

void Multime::resize() {
	// BC = WC = AC = Genetal = Theta(n)
	this->capacity *= 2;
	TElem* new_elems = new TElem[this->capacity];
	for (int i = 0; i < this->total_size; i++) {
		new_elems[i] = this->elems[i];
	}
	delete[] this->elems;
	this->elems = new_elems;
}

bool Multime::adauga(TElem elem) {
	// BC = Theta(1)
	// WC = Theta(n)
	// AC = Theta(n)
	// General = O(n)
	if (cauta(elem) == true) {
		return false;
	}

	int i = 0;
	for (; i < this->total_size && rel(this->elems[i], elem); i++);

	if (this->total_size == this->capacity) {
		resize();
	}

	for (int j = this->total_size; j > i; j--) {
		this->elems[j] = this->elems[j - 1];
	}

	this->elems[i] = elem;
	this->total_size++;

	return true;
}


bool Multime::sterge(TElem elem) {
	// BC = WC = AC = General = Theta(n)
	if (cauta(elem) == false) {
		return false;
	}

	int i = 0;
	for (; i < this->total_size && this->elems[i] != elem; i++);
	for (int j = i; j < this->total_size - 1; j++) {
		this->elems[j] = this->elems[j + 1];
	}
	this->total_size--;
	return true;
}


bool Multime::cauta(TElem elem) const {
	// BC = Theta(1)
	// WC = Theta(log n)
	// AC = Theta(log n)
	// General = O(log n)
	int start = 0, end = this->total_size - 1;
	while (start <= end) {
		int mid = (start + end) / 2;
		if (this->elems[mid] == elem) {
			return true;
		}
		if (this->relation(this->elems[mid], elem)) {
			start = mid + 1;
		}
		else {
			end = mid - 1;
		}
	}
	return false;
}

int Multime::dim() const {
	// BC = WC = AC = Genetal = Theta(1)
	return this->total_size;
}

bool Multime::vida() const {
	// BC = WC = AC = Genetal = Theta(1)
	return this->total_size == 0;
}

IteratorMultime Multime::iterator() const {
	// BC = WC = AC = Genetal = Theta(1)
	return IteratorMultime(*this);
}

Multime::~Multime() {
	// BC = WC = AC = Genetal = Theta(1)
	delete[] this->elems;
	this->elems = nullptr;
}






