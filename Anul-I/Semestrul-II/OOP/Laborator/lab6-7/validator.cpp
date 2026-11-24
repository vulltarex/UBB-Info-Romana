#include "validator.h"

void Validator::validate(const Activitate& a) const {
	std::string errors = "";
	if (a.get_titlu() == "") errors += "Titlul nu poate fi vid!\n";
	if (a.get_descriere() == "") errors += "Descrierea nu poate fi vida!\n";
	if (a.get_tip() == "") errors += "Tipul nu poate fi vid!\n";
	if (a.get_durata() <= 0) errors += "Durata trebuie sa fie strict pozitiva!\n";
	
	if (!errors.empty()) throw ValidationException(errors);
}