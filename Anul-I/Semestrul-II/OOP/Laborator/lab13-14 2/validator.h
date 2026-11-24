#pragma once
#include "activitate.h"

class ValidationException {
private:
	std::string msg;
public:
	ValidationException(const std::string& msg) : msg{ msg } {};
	const std::string& get_msg() const noexcept { return this->msg; }
};

class Validator {
public:
	/*
	Valideaza datele unei activitati
	Pre: a - referinta constanta catre o activitate
	Post: functia se incheie cu succes daca datele sunt valide (stringuri nevide si durata strict pozitiva)
	Exceptii: ValidationException daca nu sunt respectate conditiile
	*/
	void validate(const Activitate& a) const;
};