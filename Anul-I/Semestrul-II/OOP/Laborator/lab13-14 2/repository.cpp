#include "repository.h"
#include <fstream>
#include <sstream>

int Repository::repo_find_index(const std::string& titlu, const std::string& tip) const {
	auto it = std::find_if(activitati.begin(), activitati.end(), [&titlu, &tip](const Activitate& act) {
		return act.get_titlu() == titlu && act.get_tip() == tip;
		});
	if (it != activitati.end()) {
		const int index = static_cast<int>(std::distance(activitati.begin(), it));
		return index;
	}
	return -1;
}

void Repository::repo_add(const Activitate& a) {
	if (repo_find_index(a.get_titlu(), a.get_tip()) != -1) {
		throw RepoException("Activitate deja existenta!\n");
	}
	activitati.push_back(a);
}

void Repository::repo_delete(const std::string& titlu, const std::string& tip) {
	const int poz = repo_find_index(titlu, tip);
	if (poz == -1) {
		throw RepoException("Activitatea nu exista!\n");
	}
	activitati.erase(activitati.begin() + poz);
}

const Activitate& Repository::repo_find(const std::string& titlu, const std::string& tip) const {
	int index = repo_find_index(titlu, tip);
	if (index == -1) throw RepoException("Activitatea nu exista!\n");
	return activitati.at(index);
}

void Repository::repo_update(const Activitate& a) {
	const int poz = repo_find_index(a.get_titlu(), a.get_tip());
	if (poz == -1) {
		throw RepoException("Activitatea nu exista!\n");
	}
	activitati.at(poz) = a;
}

const std::vector<Activitate> Repository::repo_get_all() const {
	return activitati;
}

RepoFile::RepoFile(const std::string& filename) : Repository(), filename{ filename } {
	loadFromFile();
}

void RepoFile::loadFromFile() {
	std::ifstream in(filename);
	if (!in.is_open()) {
		return;
	}
	std::string line;
	while (std::getline(in, line)) {
		if (line.empty()) continue;

		std::stringstream ss(line);
		std::string titlu, descriere, tip, durata_str;

		std::getline(ss, titlu, ',');
		std::getline(ss, descriere, ',');
		std::getline(ss, tip, ',');
		std::getline(ss, durata_str, ',');

		int durata = std::stoi(durata_str);
		Activitate a{ titlu, descriere, tip, durata };

		Repository::repo_add(a);
	}
	in.close();
}

void RepoFile::saveToFile() {
	std::ofstream out(filename);
	if (!out.is_open()) {
		throw RepoException("Eroare la deschiderea fisierului pentru scriere!\n");
	}
	for (const auto& a : repo_get_all()) {
		out << a.get_titlu() << ","
			<< a.get_descriere() << ","
			<< a.get_tip() << ","
			<< a.get_durata() << "\n";
	}
	out.close();
}

void RepoFile::repo_add(const Activitate& a) {
	Repository::repo_add(a);
	saveToFile();
}

void RepoFile::repo_delete(const std::string& titlu, const std::string& tip) {
	Repository::repo_delete(titlu, tip);
	saveToFile();
}

void RepoFile::repo_update(const Activitate& a) {
	Repository::repo_update(a);
	saveToFile();
}

void RepoNou::throw_random() const {
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	if (dist(mt) < probabilitate) throw RepoException("Necastigator\n");
}

void RepoNou::repo_add(const Activitate& a) {
	throw_random();
	std::string cheie = a.get_titlu() + '|' + a.get_tip();
	if (dict_activitati.find(cheie) != dict_activitati.end()) {
		throw RepoException("Activitate existenta!\n");
	}
	dict_activitati.insert({ cheie,a });
}

void RepoNou::repo_delete(const std::string& titlu, const std::string& tip) {
	throw_random();
	std::string cheie = titlu + '|' + tip;
	if (dict_activitati.find(cheie) == dict_activitati.end()) {
		throw RepoException("Activitate inexistenta!\n");
	}
	dict_activitati.erase(cheie);
}

void RepoNou::repo_update(const Activitate& a) {
	throw_random();
	std::string cheie = a.get_titlu() + '|' + a.get_tip();
	if (dict_activitati.find(cheie) == dict_activitati.end()) {
		throw RepoException("Activitate inexistenta!\n");
	}
	dict_activitati.at(cheie) = a;
}

const Activitate& RepoNou::repo_find(const std::string& titlu, const std::string& tip) const {
	throw_random();
	std::string cheie = titlu + '|' + tip;
	if (dict_activitati.find(cheie) == dict_activitati.end()) {
		throw RepoException("Activitate inexistenta!\n");
	}
	return dict_activitati.at(cheie);
}

const std::vector<Activitate> RepoNou::repo_get_all() const {
	throw_random();
	std::vector<Activitate> activitati;
	for (const auto& pereche : dict_activitati) {
		activitati.push_back(pereche.second);
	}
	return activitati;
}


