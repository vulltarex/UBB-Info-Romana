#pragma once
#include "activitate.h"
#include <vector>
#include <random>
#include <map>
#include <algorithm>

class RepoException {
private:
	std::string msg;
public:
	RepoException(const std::string& msg) : msg{ msg } {};
	const std::string& get_msg() const noexcept { return this->msg; }
};

class RepoAbstract {
public:
	virtual void repo_add(const Activitate& a) = 0;
	virtual void repo_delete(const std::string& titlu, const std::string& tip) = 0;
	virtual void repo_update(const Activitate& a) = 0;
	virtual const Activitate& repo_find(const std::string& titlu, const std::string& tip) const = 0;
	virtual const std::vector<Activitate> repo_get_all() const = 0;

	virtual ~RepoAbstract() = default;
};

class Repository : public RepoAbstract{
private:
	std::vector<Activitate> activitati;
	int repo_find_index(const std::string& titlu, const std::string& tip) const;
public:
	Repository() noexcept = default;

	/*
	Cauta o activitate in lista dupa identificatorii unici
	Pre: titlu, tip - string
	Post: este returnat indexul activitatii daca a fost gasita, -1 in caz contrar
	*/
	const Activitate& repo_find(const std::string& titlu, const std::string& tip) const override;
	/*
	Adauga o noua activitate in repo
	Pre: a - referinta constanta la o Activitate
	Post: activitatea este salvata la finalul listei
	Exceptii: RepoException daca o activitate cu acelasi titlu si tip exista deja
	*/
	void repo_add(const Activitate& a) override;
	/*
	Sterge o activitate din repo
	Pre: titlu, tip - string-uri ce identifica o activitate existenta
	Post: activitatea este eliminata din lista
	Exceptii: RepoException daca activitatea cautata nu exista
	*/
	void repo_delete(const std::string& titlu, const std::string& tip) override;
	/*
	Actualizeaza datele unei activitati existente
	Pre: a - referinta constanta la o Activitate ale carei titlu si tip exista in depozit
	Post: descrierea si durata veche sunt suprascrise cu noile date
	Exceptii: RepoException daca activitatea nu a putut fi gasita
	*/
	void repo_update(const Activitate& a) override;
	/*
	Returneaza intreaga lista de activitati salvate
	Post: este returnata o referinta constanta catre vectorul de activitati
	*/
	const std::vector<Activitate> repo_get_all() const override;
};

class RepoFile : public Repository {
private:
	std::string filename;

	void loadFromFile();

	void saveToFile();

public:
	RepoFile(const std::string& filename);

	void repo_add(const Activitate& a) override;
	void repo_delete(const std::string& titlu, const std::string& tip) override;
	void repo_update(const Activitate& a) override;
};

class RepoNou : public RepoAbstract {
private:
	double probabilitate;
	std::map<std::string, Activitate> dict_activitati;
	void throw_random() const;
public:
	RepoNou(double prob) : probabilitate{ prob } {}
	void repo_add(const Activitate& a) override;
	void repo_delete(const std::string& titlu, const std::string& tip) override;
	void repo_update(const Activitate& a) override;
	const Activitate& repo_find(const std::string& titlu, const std::string& tip) const override;
	const std::vector<Activitate> repo_get_all() const override;
};