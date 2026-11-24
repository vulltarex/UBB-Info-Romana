#pragma once
#include "instrument.h"
#include <vector>

class Repo {
private:
	std::vector<Instrument> instrumente;
	std::string filename;

	void loadFromFile();
public:
	//creeaza o instanta valida Repo
	//pre: filename este un sir de caractere reprezentand numele unui fisier valid
	//post: este creata o instanta Repo cu acces de citire la fisierul cu numele furnizat
	Repo(const std::string& filename);
	//returneaza toate instrumentele stocate
	//post: este returnata o referinta catre un vector continand toate instrumentele stocate
	std::vector<Instrument>& repoGetAll();
};