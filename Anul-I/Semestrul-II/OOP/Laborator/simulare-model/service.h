#pragma once
#include "repo.h"

class Service {
private:
	Repo& repo;
public:
	//creeaza o instanta Service cu acces la un repo valid
	//pre: repo este o instanta Repo valida
	//post: este construit un obiect Service ce are acces la un repo valid
	Service(Repo& repo) : repo{ repo } {}
	//filtreaza instrumentele in functie de brand
	//pre: brand - sir de caractere reprezentand un brand
	//post: este returnat un vector ce contine doar instrumentele cu brandul furnizat
	const std::vector<Instrument> srvFilterBrand(const std::string& brand) const;
	//filtreaza instrumentele in functie de cod
	//pre: cod - numar intreg reprezentand un cod
	//post: este returnat un vector ce contine doar instrumentele cu codul furnizat
	const std::vector<Instrument> srvFilterCod(int cod) const;
	//returneaza toate instrumentele stocate
	//post: este returnata o referinta catre un vector continand toate instrumentele stocate
	const std::vector<Instrument>& srvGetAll() const;
};