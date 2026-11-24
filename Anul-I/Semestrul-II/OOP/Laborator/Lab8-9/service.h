#pragma once
#include "repository.h"
#include "validator.h"
#include "lista_activitati.h"
#include "raport.h"
#include "undo.h"

class ServiceException {
private:
	std::string msg;
public:
	ServiceException(const std::string& msg) : msg { msg } {}
	const std::string& get_msg() const noexcept { return msg; };
};

class Service {
private:
	RepoAbstract& repo;
	Validator& validator;
	ListaActivitati& lista;
	std::vector<std::unique_ptr<ActiuneUndo>> undo_actions;
public:
	Service(RepoAbstract& repo, Validator& validator, ListaActivitati& lista) noexcept : repo{ repo }, validator{ validator }, lista{ lista } {}

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
	const std::vector<Activitate> srv_get_all() const;

	/*
	Returneaza o lista cu activitatile care au o anumita descriere
	Pre: descriere - string reprezentand descrierea cautata
	Post: returneaza un VectorDinamic nou ce contine doar elementele corespunzatoare
	*/
	std::vector<Activitate> srv_filtrare_desc(const std::string& descriere) const;

	/*
	Returneaza o lista cu activitatile care sunt de un anumit tip
	Pre: tip - string reprezentand tipul cautat
	Post: returneaza un VectorDinamic nou ce contine doar elementele corespunzatoare
	*/
	std::vector<Activitate> srv_filtrare_tip(const std::string& tip) const;

	/*
	Returneaza o lista cu toate activitatile, sortate crescator dupa titlu
	Post: este returnat un VectorDinamic sortat alfabetic dupa titlu
	*/
	const std::vector<Activitate> srv_sort_titlu() const;

	/*
	Returneaza o lista cu toate activitatile, sortate crescator dupa descriere
	Post: este returnat un VectorDinamic sortat alfabetic dupa descriere
	*/
	const std::vector<Activitate> srv_sort_desc() const;

	/*
	Returneaza o lista cu toate activitatile, sortate crescator in functie de tip si durata
	Post: este returnat un VectorDinamic sortat dupa 2 criterii
	*/
	const std::vector<Activitate> srv_sort_tip_durata() const;

	/*
	Goleste lista cu activitatile curente
	Post: lista cu activitati devine vida
	*/
	void srv_clear_list() noexcept;

	/*
	Se adauga in lista prima activitate gasita in repo ce are acelasi titlu cu cel furnizat
	Pre: titlu - string nevid
	Post: Activitatea cautata este adaugata in lista cu activitati
	Exceptii: ServiceException daca nu exista nicio activitate cu titlul furnizat
	*/
	void srv_add_to_list(const std::string& titlu);

	/*
	Exporta lista curenta intr un fisier .csv sau .html
	Pre: filename - string ce reprezinta un nume valid de fisier cu extensia .csv sau .html
	Post: este exportata
	*/
	void srv_export_list(const std::string& filename) const;

	void srv_generate_list(int count);

	const size_t srv_get_list_size() const noexcept;

	std::map<std::string, int> srv_creare_raport() const;

	void srv_undo();
};