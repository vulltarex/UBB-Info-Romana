#include "repository.h"

int Repository::repo_search(const std::string& titlu, const std::string& tip) const {
	for (int it = 0; it < activitati.size(); it++) {
		if (activitati.at(it).get_titlu() == titlu && activitati.at(it).get_tip() == tip) {
			return it;
		}
	}
	return -1;
}

void Repository::repo_add(const Activitate& a) {
	if (repo_search(a.get_titlu(), a.get_tip()) != -1) {
		throw RepoException("Activitate deja existenta!\n");
	}
	activitati.push_back(a);
}

void Repository::repo_delete(const std::string& titlu, const std::string& tip) {
	const int poz = repo_search(titlu, tip);
	if (poz == -1) {
		throw RepoException("Activitatea nu exista!\n");
	}
	activitati.erase(poz);
}

const Activitate& Repository::repo_get_activitate(int index) const {
	if (index < 0 || index >= activitati.size()) throw RepoException("Activitatea nu exista!\n");
	return activitati.at(index);
}

void Repository::repo_update(const Activitate& a) {
	const int poz = repo_search(a.get_titlu(), a.get_tip());
	if (poz == -1) {
		throw RepoException("Activitatea nu exista!\n");
	}
	activitati.at(poz) = a;
}

const VectorDinamic<Activitate>& Repository::repo_get_all() const noexcept {
	return activitati;
}