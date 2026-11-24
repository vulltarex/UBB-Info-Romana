#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>

#include <exception>
using namespace std;

#define INITIAL_CAPACITY 10
#define ALPHA 0.8
#define BETA 0.8


MDOElem::MDOElem(TCheie key) {
	// BC = WC = AC = General = Theta(1)
	this->key = key;
	this->size = 0;
	this->capacity = INITIAL_CAPACITY;
	this->values = new TValoare[this->capacity];
}

MDOElem::~MDOElem() {
	// BC = WC = AC = General = Theta(1)
	delete[] this->values;
	this->values = nullptr;
}

void MDOElem::resize(int new_capacity) {
	// BC = WC = AC = General = Theta(m)
	TValoare* new_values = new TValoare[new_capacity];
	for (int i = 0; i < min(this->size, new_capacity); i++) {
		new_values[i] = this->values[i];
	}
	delete[] this->values;
	this->values = new_values;
	this->capacity = new_capacity;
}

void MDOElem::add_value(TValoare v) {
	// BC = Theta(1)
	// WC = Theta(m)
	// AC = Theta(1)
	// General = Theta(1) amortizat
	if (this->size >= ALPHA * this->capacity) {
		this->resize(this->capacity * 2);
	}
	this->values[this->size++] = v;
}


vector<TValoare> MDOElem::get_all() const {
	// BC = WC = AC = General = Theta(m)
	vector<TValoare> values;
	for (int i = 0; i < this->size; i++) {
		values.push_back(this->values[i]);
	}
	return values;
}

bool MDOElem::delete_value(TValoare v) {
	// BC = WC = AC = General = Theta(m)
	int i = 0;
	for (i = 0; i < this->size; i++) {
		if (v == this->values[i]) {
			break;
		}
	}
	if (i >= this->size) {
		return false;
	}
	for (; i < this->size - 1; i++) {
		this->values[i] = this->values[i + 1];
	}
	this->size--;
	if (this->size < BETA * this->capacity / 2) {
		this->resize(capacity / 2);
	}
	return true;
}

TCheie MDOElem::get_key() const {
	// BC = WC = AC = General = Theta(1)
	return this->key;
}

int MDOElem::get_size() const {
	// BC = WC = AC = General = Theta(1)
	return this->size;
}

MDO::MDO(Relatie r) {
	// BC = WC = AC = General = Theta(1)
	this->relation = r;
	this->used_capacity = 0;
	this->total_size = 0;
	this->capacity = INITIAL_CAPACITY;
	this->elements = new MDOElem*[this->capacity];
}

void MDO::resize(int new_capacity) {
	// BC = WC = AC = General = Theta(n)
	MDOElem** new_elements = new MDOElem*[new_capacity];
	for (int i = 0; i < min(this->used_capacity, new_capacity); i++) {
		new_elements[i] = this->elements[i];
	}
	delete[] this->elements;
	this->elements = new_elements;
	this->capacity = new_capacity;
}

int MDO::binary_search(TCheie key) const {
	// BC = Theta(1)
	// WC = Theta(log(n))
	// AC = Theta(log(n))
	// General = O(log(n))
	int start = 0, end = this->used_capacity;
	while (start < end) {
		int mid = (start + end) / 2;
		TCheie found_key = this->elements[mid]->get_key();
		if (found_key == key) {
			return mid;
		}
		if (this->relation(found_key, key)) {
			start = mid + 1;
		}
		else {
			end = mid;
		}
	}
	return -1;
}

void MDO::adauga(TCheie c, TValoare v) {
	// BC = Theta(1)
	// WC = Theta(max(log(n) + m, n))
	// AC = Theta(n)
	// General = O(n)
	this->total_size++;
	int index = this->binary_search(c);
	if (-1 != index) {
		this->elements[index]->add_value(v);
		return;
	}
	if (this->used_capacity >= ALPHA * this->capacity) {
		this->resize(this->capacity * 2);
	}
	this->elements[this->used_capacity] = new MDOElem(c);
	this->elements[this->used_capacity]->add_value(v);
	this->used_capacity++;
	for (int i = this->used_capacity - 1;
		i > 0 && this->relation(
			this->elements[i]->get_key(),
			this->elements[i - 1]->get_key()
		); i--) {
		MDOElem* aux = this->elements[i];
		this->elements[i] = this->elements[i - 1];
		this->elements[i - 1] = aux;
	}
}

vector<TValoare> MDO::cauta(TCheie c) const {
	// BC = Theta(min(log(n), m))
	// WC = Theta(log(n) + m)
	// AC = Theta(log(n) + m)
	// General = O(log(n) + m)
	int index = this->binary_search(c);
	if (-1 == index) {
		return vector<TValoare>();
	}
	return this->elements[index]->get_all();
}

bool MDO::sterge(TCheie c, TValoare v) {
	// BC = Theta(min(log(n), m)
	// WC = Theta(max(n, log(n) + m))
	// AC = Theta(max(n, log(n) + m))
	// General = O(max(n, log(n) + m))
	int index = this->binary_search(c);
	if (-1 == index) {
		return false;
	}
	bool was_deleted = this->elements[index]->delete_value(v);
	if (!was_deleted) {
		return false;
	}
	this->total_size--;
	if (this->elements[index]->get_size() > 0) {
		return true;
	}
	for (int i = index; i < this->used_capacity - 1; i++) {
		this->elements[i] = this->elements[i + 1];
	}
	this->used_capacity--;
	if (this->used_capacity < BETA * this->capacity / 2) {
		this->resize(this->capacity / 2);
	}
	return true;
}

int MDO::dim() const {
	// BC = WC = AC = General = Theta(1)
	return this->total_size;
}

bool MDO::vid() const {
	// BC = WC = AC = General = Theta(1)
	return this->total_size == 0;
}

IteratorMDO MDO::iterator() const {
	// BC = WC = AC = General = Theta(m)
	return IteratorMDO(*this);
}

MDO::~MDO() {
	// BC = WC = AC = General = Theta(n)
	for (int i = 0; i < this->used_capacity; i++) {
		delete this->elements[i];
	}
	delete[] this->elements;
	this->elements = nullptr;
}
