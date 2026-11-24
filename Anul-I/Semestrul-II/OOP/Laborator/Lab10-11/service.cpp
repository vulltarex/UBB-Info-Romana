#include "service.h"
#include <random>
#include <algorithm>
#include <chrono>

void Service::srv_add(const std::string& titlu, const std::string& descriere, const std::string& tip, int durata) {
	Activitate a = Activitate(titlu, descriere, tip, durata);
	validator.validate(a);
	repo.repo_add(a);

	undo_actions.push_back(std::make_unique<UndoAdauga>(repo, a));
}

void Service::srv_delete(const std::string& titlu, const std::string& tip) {
	Activitate activitate_stearsa = repo.repo_find(titlu, tip);
	repo.repo_delete(titlu, tip);

	undo_actions.push_back(std::make_unique<UndoSterge>(repo, activitate_stearsa));
}

void Service::srv_update(const std::string& titlu, const std::string& descriere_noua, const std::string& tip, int durata_noua) {
	Activitate a = Activitate(titlu, descriere_noua, tip, durata_noua);
	validator.validate(a);
	Activitate activitate_veche = repo.repo_find(titlu, tip);
	repo.repo_update(a);

	undo_actions.push_back(std::make_unique<UndoModifica>(repo, activitate_veche));
}

const Activitate& Service::srv_search(const std::string& titlu, const std::string& tip) const {
	return repo.repo_find(titlu, tip);
}

const std::vector<Activitate> Service::srv_get_all() const {
	return repo.repo_get_all();
}

std::vector<Activitate> Service::srv_filtrare_desc(const std::string& descriere) const {
	std::vector<Activitate> dto;
	const auto& all = repo.repo_get_all();
	std::copy_if(all.begin(), all.end(), std::back_inserter(dto), [&descriere](const Activitate& act) {return act.get_descriere() == descriere;});
	return dto;
}
std::vector<Activitate> Service::srv_filtrare_tip(const std::string& tip) const {
	std::vector<Activitate> dto;
	const auto& all = repo.repo_get_all();
	std::copy_if(all.begin(), all.end(), std::back_inserter(dto), [&tip](const Activitate& act) {return act.get_tip() == tip;});
	return dto;
}

const std::vector<Activitate> Service::srv_sort_titlu() const
{
	std::vector<Activitate> rez = repo.repo_get_all();
	std::sort(rez.begin(), rez.end(), [](const Activitate& a1, const Activitate& a2) { return a1.get_titlu() < a2.get_titlu(); });
	return rez;
}

const std::vector<Activitate> Service::srv_sort_desc() const
{
	std::vector<Activitate> rez = repo.repo_get_all();
	std::sort(rez.begin(), rez.end(), [](const Activitate& a1, const Activitate& a2) { return a1.get_descriere() < a2.get_descriere(); });
	return rez;
}

const std::vector<Activitate> Service::srv_sort_tip_durata() const
{
	std::vector<Activitate> rez = repo.repo_get_all();
	std::sort(rez.begin(), rez.end(), [](const Activitate& a1, const Activitate& a2) { 
		if (a1.get_tip() == a2.get_tip()) {
			return a1.get_durata() < a2.get_durata();
		}
		return a1.get_tip() < a2.get_tip(); 
	});
	return rez;
}

void Service::srv_clear_list() noexcept {
	lista.clear_list();
}

void Service::srv_add_to_list(const std::string& titlu) {
	const auto& activitati = repo.repo_get_all();
	auto it = std::find_if(activitati.begin(), activitati.end(), [&titlu](const Activitate& a) {return a.get_titlu() == titlu;});
	if (it == activitati.end()) {
		throw ServiceException("Activitatea nu a fost gasita!\n");
	}
	lista.add_to_list(*it);
}

void Service::srv_export_list(const std::string& filename) const {
	if (filename.ends_with(".csv") && filename.length() > 4) {
		lista.export_csv(filename);
	}
	else if (filename.ends_with(".html") && filename.length() > 5) {
		lista.export_html(filename);
	}
	else {
		throw ServiceException("Filename sau extensie invalida!");
	}
}

void Service::srv_generate_list(int count) {
	std::vector<Activitate> activitati = repo.repo_get_all();
	if (lista.get_size() != 0) {
		lista.clear_list();
	}
	if (count > activitati.size() || count <= 0) {
		throw ServiceException("Numar invalid!\n");
	}
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(activitati.begin(), activitati.end(), std::default_random_engine(static_cast<unsigned int>(seed)));

	for (int i = 0; i < count; i++) {
		lista.add_to_list(activitati.at(i));
	}
}

const size_t Service::srv_get_list_size() const noexcept {
	return lista.get_size();
}

std::map<std::string, int> Service::srv_creare_raport() const {
	RaportDTO r;
	for (const Activitate& a : repo.repo_get_all()) {
		r.incrementare_raport(a.get_tip());
	}
	return r.get_raport();
}

void Service::srv_undo() {
	if (undo_actions.empty()) {
		throw ServiceException("Nu mai exista operatii pentru undo!\n");
	}

	undo_actions.back()->doUndo();
	undo_actions.pop_back();
}