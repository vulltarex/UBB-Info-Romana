#pragma once
#include "domain.h"
#include "vector_dinamic.h"

class RepoException {
private:
	std::string msg;
public:
	RepoException(const std::string& msg) : msg{ msg } {};
	const std::string& get_msg() const noexcept { return this->msg; }
};

class Repository {
private:
	VectorDinamic<Activitate> activitati;
public:
	Repository() noexcept = default;

	/*
	Cauta o activitate in lista dupa identificatorii unici
	Pre: titlu, tip - string
	Post: este returnat indexul activitatii daca a fost gasita, -1 in caz contrar
	*/
	int repo_search(const std::string& titlu, const std::string& tip) const;
	/*
	Adauga o noua activitate in repo
	Pre: a - referinta constanta la o Activitate
	Post: activitatea este salvata la finalul listei
	Exceptii: RepoException daca o activitate cu acelasi titlu si tip exista deja
	*/
	void repo_add(const Activitate& a);
	/*
	Sterge o activitate din repo
	Pre: titlu, tip - string-uri ce identifica o activitate existenta
	Post: activitatea este eliminata din lista
	Exceptii: RepoException daca activitatea cautata nu exista
	*/
	void repo_delete(const std::string& titlu, const std::string& tip);
	/*
	Returneaza o activitate aflata pe o pozitie specifica
	Pre: index - numar intreg valid
	Post: este returnata o referinta constanta catre activitate
	Exceptii: RepoException daca indexul este in afara limitelor vectorului
	*/
	const Activitate& repo_get_activitate(int index) const;
	/*
	Actualizeaza datele unei activitati existente
	Pre: a - referinta constanta la o Activitate ale carei titlu si tip exista in depozit
	Post: descrierea si durata veche sunt suprascrise cu noile date
	Exceptii: RepoException daca activitatea nu a putut fi gasita
	*/
	void repo_update(const Activitate& a);
	/*
	Returneaza intreaga lista de activitati salvate
	Post: este returnata o referinta constanta catre vectorul de activitati
	*/
	const VectorDinamic<Activitate>& repo_get_all() const noexcept;
};