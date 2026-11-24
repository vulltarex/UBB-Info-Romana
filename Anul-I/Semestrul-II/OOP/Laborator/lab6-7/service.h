#pragma once
#include "repository.h"
#include "validator.h"

class Service {
private:
	Repository& repo;
	Validator& validator;

	/*
	Algoritm de sortare ce opereaza pe un vector in functie de relatia data
	Pre: rez - referinta la un VectorDinamic, cmp_func - pointer catre o functie bool de comparare
	Post: vectorul rez este sortat in-place
	*/
	void sort(VectorDinamic<Activitate>& rez, bool(*cmp_func)(const Activitate& a1, const Activitate& a2)) const;

	/*
	Compara doua activitati in functie de titlu
	Post: returneaza true daca a1 < a2 (alfabetic), false altfel
	*/
	static bool cmp_titlu(const Activitate& a1, const Activitate& a2) noexcept;

	/*
	Compara doua activitati in functie de descriere
	Post: returneaza true daca a1 < a2 (alfabetic), false altfel
	*/
	static bool cmp_desc(const Activitate& a1, const Activitate& a2) noexcept;

	/*
	Compara doua activitati in functie de tip, iar la egalitate in functie de durata lor
	Post: returneaza true daca a1 trebuie plasata inaintea lui a2 in lista sortata, false altfel
	*/
	static bool cmp_tip_durata(const Activitate& a1, const Activitate& a2) noexcept;
public:
	Service(Repository& repo, Validator& validator) noexcept : repo { repo }, validator{ validator }{} ;

	/*
	Creeaza, valideaza si adauga o noua activitate in aplicatie
	Pre: titlu, descriere, tip - string, durata - int
	Post: activitatea este adaugata cu succes in repository
	Exceptii: ValidationException daca datele sunt invalide; RepoException daca activitatea e duplicat
	*/
	void srv_add(const std::string& titlu, const std::string& descriere, const std::string& tip, int durata);

	/*
	Deleaga stergerea unei activitati catre repository
	Pre: titlu, tip - string
	Post: activitatea este stearsa
	Exceptii: RepoException daca activitatea nu exista in lista
	*/
	void srv_delete(const std::string& titlu, const std::string& tip);

	/*
	Valideaza datele noi si deleaga modificarea unei activitati
	Pre: titlu, descriere_noua, tip - string, durata_noua - int
	Post: atributele vechi sunt suprascrise
	Exceptii: ValidationException daca noile date sunt invalide; RepoException daca activitatea nu exista
	*/
	void srv_update(const std::string& titlu, const std::string& descriere_noua, const std::string& tip, int durata_noua);

	/*
	Cauta o activitate dupa titlu si tip
	Pre: titlu, tip - string
	Post: este returnata o referinta constanta la activitatea ceruta
	Exceptii: RepoException daca nu a fost gasita
	*/
	const Activitate& srv_search(const std::string& titlu, const std::string& tip) const;

	/*
	Returneaza o referinta constanta catre toate activitatile stocate
	Post: este returnata lista intreaga din repo
	*/
	const VectorDinamic<Activitate>& srv_get_all() const noexcept;

	/*
	Returneaza o lista cu activitatile care au o anumita descriere
	Pre: descriere - string reprezentand descrierea cautata
	Post: returneaza un VectorDinamic nou ce contine doar elementele corespunzatoare
	*/
	VectorDinamic<Activitate> srv_filtrare_desc(const std::string& descriere) const;

	/*
	Returneaza o lista cu activitatile care sunt de un anumit tip
	Pre: tip - string reprezentand tipul cautat
	Post: returneaza un VectorDinamic nou ce contine doar elementele corespunzatoare
	*/
	VectorDinamic<Activitate> srv_filtrare_tip(const std::string& tip) const;

	/*
	Returneaza o lista cu toate activitatile, sortate crescator dupa titlu
	Post: este returnat un VectorDinamic sortat alfabetic dupa titlu
	*/
	VectorDinamic<Activitate> srv_sort_titlu() const;

	/*
	Returneaza o lista cu toate activitatile, sortate crescator dupa descriere
	Post: este returnat un VectorDinamic sortat alfabetic dupa descriere
	*/
	VectorDinamic<Activitate> srv_sort_desc() const;

	/*
	Returneaza o lista cu toate activitatile, sortate crescator in functie de tip si durata
	Post: este returnat un VectorDinamic sortat dupa 2 criterii
	*/
	VectorDinamic<Activitate> srv_sort_tip_durata() const;
};