#pragma once
#include <memory>
#include <utility>
#include <stdexcept>

#pragma warning(push)
#pragma warning(disable: 26446)
#pragma warning(disable: 26458)

template<typename elem_type>
class VectorDinamic {
public:
	/*
	Constructor default pentru vectorul dinamic
	Post: este creat un vector gol cu lungime 0
	*/
	VectorDinamic() noexcept;
	/*
	Constructor de copiere
	Pre: other - referinta constanta la un VectorDinamic
	Post: este creata o copie profunda (deep copy) a vectorului transmis
	*/
	VectorDinamic(const VectorDinamic& other);
	/*
	Operator de atribuire prin copiere
	Pre: other - referinta constanta la un VectorDinamic
	Post: resursele curente sunt eliberate si inlocuite cu o copie profunda a lui 'other'
	*/
	VectorDinamic<elem_type>& operator=(const VectorDinamic& other);
	/*
	Constructor de mutare
	Pre: other - o referinta r-value la un VectorDinamic temporar
	Post: datele din 'other' sunt transferate in obiectul curent, iar 'other' este golit
	*/
	VectorDinamic(VectorDinamic&& other) noexcept;
	/*
	Operator de atribuire prin mutare
	Pre: other - o referinta r-value la un VectorDinamic temporar
	Post: resursele sunt transferate in obiectul curent, 'other' este golit
	*/
	VectorDinamic<elem_type>& operator=(VectorDinamic&& other) noexcept;
	//destructor
	~VectorDinamic() {}

	/*
	Returneaza referinta la elementul de la o anumita pozitie
	Pre: index - numar intreg valid (0 <= index < len)
	Post: este returnata referinta la elementul gasit
	Exceptii: std::out_of_range daca indexul este invalid
	*/
	elem_type& at(int index);
	/*
	Returneaza referinta constanta la elementul de la o anumita pozitie
	Pre: index - numar intreg valid (0 <= index < len)
	Post: este returnata referinta la elementul gasit
	Exceptii: std::out_of_range daca indexul este invalid
	*/
	const elem_type& at(int index) const;
	/*
	Returneaza numarul curent de elemente din vector
	Post: este returnat un numar natural reprezentand lungimea
	*/
	int size() const noexcept;
	/*
	Adauga un element nou la finalul vectorului
	Pre: e - referinta constanta la elementul de adaugat
	Post: elementul este adaugat pe ultima pozitie, capacitatea este redimensionata daca e necesar
	*/
	void push_back(const elem_type& e);
	/*
	Sterge elementul de pe pozitia data
	Pre: index - numar intreg valid (0 <= index < len)
	Post: elementul este eliminat din memorie, iar restul elementelor sunt deplasate spre stanga
	*/
	void erase(int index) noexcept;

private:
	std::unique_ptr<elem_type[]> elems;
	int len;
	int capacity;
	
	/*
	Dubleaza capacitatea de stocare a vectorului dinamic curent
	Post: memoria este realocata la capacitate dubla, pastrand elementele existente in aceeasi ordine
	*/
	void resize();

};
//the big five
template<typename elem_type>
VectorDinamic<elem_type>::VectorDinamic() noexcept {
	this->len = 0;
	this->capacity = 0;
	this->elems = nullptr;
}

template<typename elem_type>
VectorDinamic<elem_type>::VectorDinamic(const VectorDinamic& other) {
	this->len = other.len;
	this->capacity = other.capacity;
	this->elems = std::make_unique<elem_type[]>(this->capacity);

	for (size_t i = 0; i < static_cast<size_t>(this->len); i++) {
		this->elems[i] = other.elems[i];
	}

	std::cout << "copie\n";
}

template<typename elem_type>
VectorDinamic<elem_type>& VectorDinamic<elem_type>::operator=(const VectorDinamic& other) {
	if (this != &other) {
		this->len = other.len;
		this->capacity = other.capacity;
		this->elems = std::make_unique<elem_type[]>(this->capacity);

		for (size_t i = 0; i < static_cast<size_t>(this->len); i++) {
			this->elems[i] = other.elems[i];
		}
	}
	return *this;
}

template<typename elem_type>
VectorDinamic<elem_type>::VectorDinamic(VectorDinamic&& other) noexcept {
	this->capacity = other.capacity;
	this->len = other.len;
	this->elems = std::move(other.elems);

	other.len = 0;
	other.capacity = 0;
}

template<typename elem_type>
VectorDinamic<elem_type>& VectorDinamic<elem_type>::operator=(VectorDinamic&& other) noexcept {
	if (this != &other) {
		this->capacity = other.capacity;
		this->len = other.len;
		this->elems = std::move(other.elems);

		other.len = 0;
		other.capacity = 0;
	}
	return *this;
}

//alte metode

template<typename elem_type>
elem_type& VectorDinamic<elem_type>::at(int index) {
	if (index < 0 || index >= this->len) throw (std::out_of_range("Index invalid!\n"));
	return this->elems[index];
}

template<typename elem_type>
const elem_type& VectorDinamic<elem_type>::at(int index) const {
	if (index < 0 || index >= this->len) throw (std::out_of_range("Index invalid!\n"));
	return this->elems[index];
}

template<typename elem_type>
void VectorDinamic<elem_type>::resize() {
	if (this->capacity == 0) this->capacity = 2;
	else this->capacity *= 2;
	std::unique_ptr<elem_type[]> new_elems = std::make_unique<elem_type[]>(this->capacity);

	for (int i = 0; i < this->len; i++) {
		new_elems[i] = this->elems[i];
	}

	this->elems = std::move(new_elems);
}

template<typename elem_type>
void VectorDinamic<elem_type>::push_back(const elem_type& e) {
	if (len >= capacity) {
		resize();
	}
	elems[len++] = e;
}

template<typename elem_type>
void VectorDinamic<elem_type>::erase(int index) noexcept {
	for (size_t i = index; i < static_cast<size_t>(this->len) - 1; i++) {
		this->elems[i] = this->elems[i + 1];
	}
	this->len--;
}

template<typename elem_type>
int VectorDinamic<elem_type>::size() const noexcept {
	return this->len;
}

#pragma warning(pop)