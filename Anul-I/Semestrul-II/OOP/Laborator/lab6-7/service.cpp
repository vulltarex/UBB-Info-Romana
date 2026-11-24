#include "service.h"

void Service::srv_add(const std::string& titlu, const std::string& descriere, const std::string& tip, int durata) {
	Activitate a = Activitate(titlu, descriere, tip, durata);
	validator.validate(a);
	repo.repo_add(a);
}

void Service::srv_delete(const std::string& titlu, const std::string& tip) {
	repo.repo_delete(titlu, tip);
}

void Service::srv_update(const std::string& titlu, const std::string& descriere_noua, const std::string& tip, int durata_noua) {
	Activitate a = Activitate(titlu, descriere_noua, tip, durata_noua);
	validator.validate(a);
	repo.repo_update(a);
}

const Activitate& Service::srv_search(const std::string& titlu, const std::string& tip) const {
	const int poz = repo.repo_search(titlu, tip);
	return repo.repo_get_activitate(poz);
}

const VectorDinamic<Activitate>& Service::srv_get_all() const noexcept {
	return repo.repo_get_all();
}

VectorDinamic<Activitate> Service::srv_filtrare_desc(const std::string& descriere) const {
	VectorDinamic<Activitate> dto;
	const auto& all = repo.repo_get_all();
	for (int i = 0; i < all.size(); i++) {
		if (all.at(i).get_descriere() == descriere) {
			dto.push_back(all.at(i));
		}
	}
	return dto;
}
VectorDinamic<Activitate> Service::srv_filtrare_tip(const std::string& tip) const {
	VectorDinamic<Activitate> dto;
	const auto& all = repo.repo_get_all();
	for (int i = 0; i < all.size(); i++) {
		if (all.at(i).get_tip() == tip) {
			dto.push_back(all.at(i));
		}
	}
	return dto;
}

void Service::sort(VectorDinamic<Activitate>& rez, bool(*cmp_func)(const Activitate& a1, const Activitate& a2)) const {
	if (cmp_func == nullptr) return;
	for (int i = 0; i < rez.size(); i++) {
		for (int j = 0; j < rez.size() - i - 1; j++) {
			if (!cmp_func(rez.at(j), rez.at(j + 1))) {
				std::swap(rez.at(j), rez.at(j + 1));
			}
		}
	}
}

bool Service::cmp_titlu(const Activitate& a1, const Activitate& a2) noexcept {
	return a1.get_titlu() < a2.get_titlu();
}

bool Service::cmp_desc(const Activitate& a1, const Activitate& a2) noexcept {
	return a1.get_descriere() < a2.get_descriere();
}

bool Service::cmp_tip_durata(const Activitate& a1, const Activitate& a2) noexcept {
	if (a1.get_tip() < a2.get_tip()) return true;
	if (a1.get_tip() > a2.get_tip()) return false;
	return a1.get_durata() < a2.get_durata();
}

VectorDinamic<Activitate> Service::srv_sort_titlu() const
{
	VectorDinamic<Activitate> rez = repo.repo_get_all();
	sort(rez, cmp_titlu);
	return rez;
}

VectorDinamic<Activitate> Service::srv_sort_desc() const
{
	VectorDinamic<Activitate> rez = repo.repo_get_all();
	sort(rez, cmp_desc);
	return rez;
}

VectorDinamic<Activitate> Service::srv_sort_tip_durata() const
{
	VectorDinamic<Activitate> rez = repo.repo_get_all();
	sort(rez, cmp_tip_durata);
	return rez;
}