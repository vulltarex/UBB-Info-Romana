#pragma once
#include <string>

class Automobil {
private:
	int cod;
	std::string denumire;
	std::string tip;
	int necesarApa;
public:
	//construieste o instanta de automobil cu atributele furnizate ca parametru
	//pre: cod, necesarApa - numere intregi valide
	//post: este creata o instanta valida Automobil
	Automobil(int cod, const std::string& denumire, const std::string& tip, int necesarApa) : cod{ cod }, denumire{ denumire }, tip{ tip }, necesarApa{ necesarApa } {}
	//returneaza codul automobilului
	//post: este returnat un numar intreg reprezentand codul ce apartine automobilului
	const int getCod() const { return cod; }
	//returneaza denumirea automobilului
	//post: este returnat un sir de caractere reprezentand denumirea ce apartine automobilului
	const std::string& getDenumire() const { return denumire; }
	//returneaza tipul automobilului
	//post: este returnat un sir de caractere reprezentand tipul ce apartine automobilului
	const std::string& getTip() const { return tip; }
	//returneaza necesarul de apa al automobilului
	//post: este returnat un numar intreg reprezentand necesarul de apa in ml al automobilului
	const int getNecesarApa() const { return necesarApa; }
};