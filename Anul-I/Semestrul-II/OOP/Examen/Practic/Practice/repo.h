#pragma once
#include <fstream>
#include <vector>
#include "masina.h"
class Repo {
private:
    std::vector<Masina> masini;
    void loadFromFile();
    void saveToFile();
    std::string filename;
public:
    Repo(const std::string& filename) : filename(filename) { loadFromFile(); }
    std::vector<Masina>& getAll();
    void updateMasina(int id, int putereNoua, const std::string& stareNoua);
};