#pragma once
#include "repo.h"

class Service {
private:
	Repo& repo;
public:
	//construieste o instanta service cu acces la repo-ul furnizat
	//pre: repo - instanta valida Repo
	//post: este creata o instanta valida Service
	Service(Repo& repo) : repo{ repo } {}
	//returneaza toate automobilele stocate sortate alfabetic dupa tip
	//pre: all - vector ce contine toate automobilele stocate
	//post: este returnat un vector ce contine automobilele sortate alfabetic dupa tip
	const std::vector<Automobil> srvSortTip(const std::vector<Automobil>& all) const;
	//returneaza automobilele ce respecta criteriul
	//pre: all - vector ce contine toate automobilele stocate, cantitate - numar intreg reprezentand cantitatea maxima de apa necesara
	//post: este returnat un vector cu automobilele care necesita stric mai putin apa decat valoarea variabilei cantitate
	const std::vector<Automobil> srvFilterNecesarApa(const std::vector<Automobil>& all, const int cantitate) const;
	//returneaza toate automobilele stocate
	//post: este returnat un vector continand toate automobilele stocate
	const std::vector<Automobil>& srvGetAll() const;
};
