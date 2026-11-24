#pragma once
#include <string>
//Masini: id, specie, nume, varsta.Am avut de implementat un QTable care avea lista populata din fisier la inceput cu toate in afara de id.fiecare rand 
// trebuia colorat in functie de ce "specie" era : ex : SUV = > rand grey... Daca varsta masinii > 10  atunci cand se selecteaza randu sa apara un pop - up cu 
// "Animalul este prea in varsta!".Sa aiba 3 butoane: sortare dupa an, filtrare dupa specie si reset.
class Masina {
private:
	int id;
	std::string specie;
	std::string nume;
	int varsta;
public:
	Masina(int id, std::string& specie, std::string& nume, int varsta) : id{ id }, specie{ specie }, nume{ nume }, varsta{ varsta } {}
	const int getId() const { return id; }
	const std::string& getSpecie() const { return specie; }
	const std::string& getNume() const { return nume; }
	const int getVarsta() const { return varsta; }
};