#include "domain.h"

Activitate::Activitate(const std::string& titlu, const std::string& descriere, const std::string& tip, int durata) : titlu{ titlu }, descriere{ descriere }, tip{ tip }, durata{ durata } {}

const std::string& Activitate::get_titlu() const noexcept
{
	return titlu;
}
const std::string& Activitate::get_descriere() const noexcept
{
	return descriere;
}
const std::string& Activitate::get_tip() const noexcept
{
	return tip;
}
int Activitate::get_durata() const noexcept
{
	return durata;
}

void Activitate::set_titlu(const std::string& titlu_new) noexcept
{
	this->titlu = titlu_new;
}
void Activitate::set_descriere(const std::string& descriere_new) noexcept
{
	this->descriere = descriere_new;
}
void Activitate::set_tip(const std::string& tip_new) noexcept
{
	this->tip = tip_new;
}
void Activitate::set_durata(int durata_new) noexcept
{
	this->durata = durata_new;
}

std::ostream& operator<<(std::ostream& stream, const Activitate& a) {
	stream << "Activitate: [ Titlu: " << a.get_titlu() << ", Descriere: " << a.get_descriere() << ", Tip: " << a.get_tip() << ", Durata: " << a.get_durata() << " minute ]";
	return stream;
}

bool Activitate::operator==(const Activitate& other) const noexcept {
	return titlu == other.titlu && tip == other.tip;
}