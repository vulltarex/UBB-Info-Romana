#pragma once

#include <vector>

typedef int TCheie;
typedef int TValoare;

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

using namespace std;

class IteratorMDO;

typedef bool(*Relatie)(TCheie, TCheie);

class MDOElem {
private:
	TCheie key;
	TValoare* values;
	int capacity;
	int size;

	void resize(int new_capacity);
public:
	MDOElem(TCheie key);
	~MDOElem();

	void add_value(TValoare v);
	vector<TValoare> get_all() const;
	bool delete_value(TValoare v);

	TCheie get_key() const;
	int get_size() const;
};

class MDO {
	friend class IteratorMDO;
    private:
	/* aici e reprezentarea */
		MDOElem** elements;
		int capacity;
		int used_capacity;
		int total_size;
		Relatie relation;

		void resize(int new_capacity);
		int binary_search(TCheie key) const;
    public:

	// constructorul implicit al MultiDictionarului Ordonat
	MDO(Relatie r);

	// adauga o pereche (cheie, valoare) in MDO
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MDO 
	int dim() const;

	//verifica daca MultiDictionarul Ordonat e vid 
	bool vid() const;

	// se returneaza iterator pe MDO
	// iteratorul va returna perechile in ordine in raport cu relatia de ordine
	IteratorMDO iterator() const;

	// destructorul 	
	~MDO();

};
