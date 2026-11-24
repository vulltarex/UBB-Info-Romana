#pragma once

#include "automobil.h"
#include <vector>

class Repo {
private:
	std::vector<Automobil> automobile;
	std::string filename;

	void loadFromFile();
public:
	//creeaza o instanta Repo cu acces la fisierul cu numele furnizat
	//pre: filename - sir de caractere ce reprezinta numele unui fisier valid
	//post: este creata o instanta Repo valida cu acces la fisierul furnizat
	Repo(const std::string& filename) : filename{ filename } { loadFromFile(); }
	//returneaza toate automobilele stocate
	//post: este returnat un vector ce contine toate automobilele stocate
	const std::vector<Automobil>& repoGetAll() const;
};