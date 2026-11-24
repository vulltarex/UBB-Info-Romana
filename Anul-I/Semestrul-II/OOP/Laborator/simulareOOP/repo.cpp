#include "repo.h"
#include <fstream>
#include <sstream>

Repo::Repo(const std::string& filename) : filename{ filename } {
	loadFromFile();
}

std::vector<Instrument>& Repo::repoGetAll() {
	return instrumente;
}

void Repo::loadFromFile() {
	std::ifstream fin(filename);
	if (!fin.is_open()) throw std::exception("Fisierul nu a fost deschis!");

	std::string line;
	while (std::getline(fin, line)) {
		if (line.empty()) continue;
		std::stringstream ss(line);
		std::string codStr, tip, brand, consumEnergeticStr;
		std::getline(ss, codStr, ',');
		std::getline(ss, tip, ',');
		std::getline(ss, brand, ',');
		std::getline(ss, consumEnergeticStr, ',');
		int cod = std::stoi(codStr), consumEnergetic = std::stoi(consumEnergeticStr);
		Instrument i{ cod, tip, brand, consumEnergetic };
		instrumente.push_back(i);
	}
	fin.close();
}

