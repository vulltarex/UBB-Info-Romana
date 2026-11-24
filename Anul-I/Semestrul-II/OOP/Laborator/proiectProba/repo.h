#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include "masina.h"
class Repo {
private:
	std::vector<Masina> masini;
	std::string filename;

	void loadFromFile() {
		std::ifstream fin(filename);
		if (!fin.is_open()) throw std::exception("Fisier negasit!");

		std::string line;
		while (std::getline(fin, line)) {
			if (line.empty()) continue;
			std::stringstream ss(line);
			std::string id_str, nume, specie, varsta_str;
			std::getline(ss, id_str, ',');
			std::getline(ss, specie, ',');
			std::getline(ss, nume, ',');
			std::getline(ss, varsta_str, ',');
			int id = std::stoi(id_str);
			int varsta = std::stoi(varsta_str);
			Masina m{ id, specie, nume, varsta };
			masini.push_back(m);
		}
		fin.close();
	}

public:
	Repo(std::string& filename) : filename{ filename } {
		loadFromFile();
	}
	const std::vector<Masina>& repoGetAll() const {
		return masini;
	}
};