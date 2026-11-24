#pragma once
#include <string>

class Instrument {
private:
	int cod;
	std::string tip;
	std::string brand;
	int consumEnergetic;
public:
	//creeaza un obiect de tip instrument cu atributele corespunzatoare celor furnizate
	//pre: cod, consumEnergetic - nr intregi - tip, brand - siruri de caractere nevide
	//post: este creat obiectul de tip Instrument cu atributele initializate confrom valorilor furnizate
	Instrument(int cod, const std::string& tip, const std::string& brand, int consumEnergetic) : cod{ cod }, tip{ tip }, brand{ brand }, consumEnergetic{ consumEnergetic } {}
	//returneaza codul corespunzator Instrumentului
	//post: este returnat un numar intreg reprezentand codul instrumentului
	int getCod() const { return cod; }
	//returneaza tipul instrumentului
	//post: este returnat un sir de caractere reprezentand tipul instrumentului
	const std::string& getTip() const { return tip; }
	//returneaza brandul instrumentului
	//post: este returnat un sir de caractere reprezentand brandul instrumentului
	const std::string& getBrand() const { return brand; }
	//returneaza consumul energetic corespunzator Instrumentului
	//post: este returnat un numar intreg reprezentand consumul energetic al instrumentului
	int getConsumEnergetic() const { return consumEnergetic; }
};