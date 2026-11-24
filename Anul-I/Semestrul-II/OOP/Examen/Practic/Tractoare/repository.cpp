#include "repository.h"
#include <fstream>
#include <sstream>

void Repo::loadFromFile() {
    std::ifstream fin(filename);
    if (!fin.is_open()) throw RepoException("Eroare la deschiderea fisierului!");

    std::string line;
    while (std::getline(fin, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string idStr, denumire, tip, numarRotiStr;
        std::getline(ss, idStr, ',');
        std::getline(ss, denumire, ',');
        std::getline(ss, tip, ',');
        std::getline(ss, numarRotiStr, ',');
        int id = std::stoi(idStr);
        int numarRoti = std::stoi(numarRotiStr);
        Tractor t{id, denumire, tip, numarRoti};
        tractoare.push_back(t);
    }
    fin.close();
}

void Repo::saveToFile() {
    std::ofstream fout(filename);
    if (!fout.is_open()) throw RepoException("Eroare la deschiderea fisierului!");

    for (const auto& tr : tractoare) {
        fout << tr.getId() << ',' << tr.getDenumire() << ',' << tr.getTip() << ',' << tr.getNumarRoti() << '\n';
    }
    fout.close();
}

void Repo::repoAdd(Tractor& t) {
    for (auto& tr : tractoare)
        if (tr.getId() == t.getId())
            throw RepoException("ID existent!");
    tractoare.push_back(t);
    saveToFile();
}

const std::vector<Tractor>& Repo::repoGetAll() const {
    return tractoare;
}