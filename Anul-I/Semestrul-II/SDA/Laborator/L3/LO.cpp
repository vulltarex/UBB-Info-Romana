#include "Iterator.h"
#include "LO.h"

#include <iostream>
using namespace std;

#include <exception>

LO::LO(Relatie r) {
	// BC = WC = AC = Theta(1)
	this->first = nullptr;
	this->r = r;
	this->size = 0;
}

// returnare dimensiune
int LO::dim() const {
	// BC = WC = AC = Theta(1)
	return this->size;
}

// verifica daca LO e vida
bool LO::vida() const {
	// BC = WC = AC = Theta(1)
	return this->size == 0;
}

// returnare element
//arunca exceptie daca i nu e valid
TElement LO::element(int i) const {
	// BC = Theta(1)
	// WC = Theta(n)
	// AC = Theta(n)
	// General = O(n)
	if (i < 0 || i >= this->size) throw std::exception();
	Node* curent = this->first;
	for (int ind = 0; ind < i; ind++) curent = curent->next;
	return curent->value;
}

// sterge element de pe o pozitie i si returneaza elementul sters
//arunca exceptie daca i nu e valid
TElement LO::sterge(int i) {
	// BC = Theta(1)
	// WC = Theta(n)
	// AC = Theta(n)
	// General = O(n)
	if (i < 0 || i >= this->size) throw std::exception();
	if (i == 0) {
		Node* to_delete = this->first;
		TElement value = to_delete->value;
		this->first = to_delete->next;
		delete to_delete;
		this->size--;
		return value;
	}
	Node* curent = this->first;
	for (int ind = 0; ind < i - 1; ind++) curent = curent->next;
	Node* to_delete = curent->next;
	TElement value = to_delete->value;
	curent->next = to_delete->next;
	delete to_delete;
	this->size--;
	return value;
}

// cauta element si returneaza prima pozitie pe care apare (sau -1)
int LO::cauta(TElement e) const {
	// BC = Theta(1)
	// WC = Theta(n)
	// AC = Theta(n)
	// General = O(n)
	Node* curent = this->first;
	if (vida()) {
		return -1;
	}
	int i = 0;
	while (curent->next != nullptr && curent->value != e) {
		curent = curent->next;
		i++;
	}
	if (curent->value == e) {
		return i;
	}
	return -1;
}

// adaugare element in LO
void LO::adauga(TElement e) {
	// BC = Theta(1)
	// WC = Theta(n)
	// AC = Theta(n)
	// General = O(n)
	Node* to_add = new Node;
	to_add->value = e;
	to_add->next = nullptr;
	if (this->size == 0 || r(e, this->first->value)) {
		to_add->next = this->first;
		this->first = to_add;
		this->size++;
		return;
	}
	Node* curent = this->first;
	while (curent->next != nullptr && !r(e, curent->next->value)) {
		curent = curent->next;
	}
	to_add->next = curent->next;
	curent->next = to_add;
	this->size++;
}

// returnare iterator
Iterator LO::iterator(){
	// BC = WC = AC = Theta(1)
	return Iterator(*this);
}

//destructor
LO::~LO() {
	// BC = WC = AC = Theta(n)
	Node* curent = this->first;
	while (curent != nullptr) {
		Node* to_delete = curent;
		curent = curent->next;
		delete to_delete;
	}
}