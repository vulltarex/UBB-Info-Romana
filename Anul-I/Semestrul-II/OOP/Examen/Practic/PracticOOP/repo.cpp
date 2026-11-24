#include "repo.h"
#include <fstream>
#include <sstream>
#include <algorithm>
Repo::Repo(const std::string &filename) : filename(filename) {
    loadFromFile();
}

void Repo::loadFromFile() {
    std::ifstream fin(filename);
    if (!fin.is_open()) return;
    std::string line;
    while (getline(fin, line)) {
        std::stringstream ss(line);
        std::string nume, facultate, nrMatricolStr, varstaStr;
        std::getline(ss, nrMatricolStr, ',');
        std::getline(ss, nume, ',');
        std::getline(ss, varstaStr, ',');
        std::getline(ss, facultate, ',');
        int nrMatricol = stoi(nrMatricolStr);
        int varsta = stoi(varstaStr);
        Student s(nrMatricol, nume, varsta, facultate);
        studenti.push_back(s);
    }
    fin.close();
}

void Repo::saveToFile() {
    std::ofstream fout(filename);
    if (!fout.is_open()) return;
    for (auto& s : studenti)
        fout << s.getNrMatricol() << ',' << s.getNume() << ','
             << s.getVarsta() << ',' << s.getFacultate() <<'\n';
    fout.close();
}

void Repo::repoDelete(int id) {
    for (int i = 0; i < studenti.size(); i++){
        if (studenti.at(i).getNrMatricol() == id) {
            studenti.erase(studenti.begin() + i);
            saveToFile();
            break;
        }
    }
}

void Repo::repoUpdate(int id, int varstaNoua) {
    for (auto& s : studenti)
        if (s.getNrMatricol() == id) {
            s.setVarsta(varstaNoua);
            saveToFile();
            break;
        }
}

void Repo::repoUndo(std::vector<Student> stare) {
    studenti = stare;
}

std::vector<Student> & Repo::getAll() {
    return studenti;
}


