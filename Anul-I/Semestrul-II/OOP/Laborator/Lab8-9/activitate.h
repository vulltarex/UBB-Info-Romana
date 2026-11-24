#pragma once
#include <string>
#include <iostream>

class Activitate {
private:
	std::string titlu{ "" };
	std::string descriere{ "" };
	std::string tip{ "" };
	int durata{ 0 };
public:
	Activitate() = default;
	/*
	Constructor pt initializarea unei activitati
	Pre: titlu, descriere, tip - string, durata - int
	Post: este creata un obiect Activitate cu atributele date
	*/
	Activitate(const std::string& titlu, const std::string& descriere, const std::string& tip, int durata);

	/*
	Returneaza titlul activitatii
	Post: Este returnata referinta constanta la string-ul corespunzator
	*/
	const std::string& get_titlu() const noexcept;
	/*
	Returneaza descrierea activitatii
	Post: Este returnata referinta constanta la string-ul corespunzator
	*/
	const std::string& get_descriere() const noexcept;
	/*
	Returneaza tipul activitatii
	Post: Este returnata referinta constanta la string-ul corespunzator
	*/
	const std::string& get_tip() const noexcept;
	/*
	Returneaza durata activitatii
	Post: Este returnat un numar intreg reprezentand durata
	*/
	int get_durata() const noexcept;

	/*
	Modifica valoarea atributului titlu
	Pre: titlu_new - string
	Post: atributul este actualizat cu noua valoare
	*/
	void set_titlu(const std::string& titlu_new) noexcept;
	/*
	Modifica valoarea atributului descriere
	Pre: descriere_new - string
	Post: atributul este actualizat cu noua valoare
	*/
	void set_descriere(const std::string& descriere_new) noexcept;
	/*
	Modifica valoarea atributului tip
	Pre: tip_new - string
	Post: atributul este actualizat cu noua valoare
	*/
	void set_tip(const std::string& tip_new) noexcept;
	/*
	Modifica valoarea atributului durata
	Pre: durata_new - int
	Post: atributul este actualizat cu noua valoare
	*/
	void set_durata(int durata_new) noexcept;

	//suprascrie operatorul << al fluxului de iesire pentru a afisa atributele activitatii
	friend std::ostream& operator<<(std::ostream& stream, const Activitate& a);
	/*
	Verifica egalitatea dintre doua activitati. Doua activitati sunt considerate egale daca au acelasi titlu si tip
	Post: returneaza true in caz de egalitate, false altfel
	*/
	bool operator==(const Activitate& ot) const noexcept;
};