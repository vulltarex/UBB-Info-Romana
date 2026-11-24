#include "repo.h"
#include <fstream>
#include <sstream>

void Repo::loadFromFile() {
	std::ifstream fin(filename);
	if (!fin.is_open()) {
		return;
	}

	std::string line;
	while (std::getline(fin, line)) {
		if (line.empty()) continue;
		std::stringstream ss(line);
		std::string codStr, denumire, tip, necesarApaStr;
		std::getline(ss, codStr, ',');
		std::getline(ss, denumire, ',');
		std::getline(ss, tip, ',');
		std::getline(ss, necesarApaStr, ',');
		int cod = std::stoi(codStr);
		int necesarApa = std::stoi(necesarApaStr);
		Automobil a{ cod, denumire, tip, necesarApa };
		automobile.push_back(a);
	}
	fin.close();
}

const std::vector<Automobil>& Repo::repoGetAll() const {
	return automobile;
}


