#include "Repo.h"
#include <fstream>
#include <sstream>

void Repo::loadFromFile()
{
    std::ifstream fin(filename);
    if (!fin.is_open())
    {
        return;
    }

    std::string line;
    while (std::getline(fin, line))
    {
        std::stringstream ss(line);
        std::string id_str, model, putere_str, stare;

        std::getline(ss, id_str, ',');
        std::getline(ss, model, ',');
        std::getline(ss, putere_str, ',');
        std::getline(ss, stare, ',');

        if (!model.empty() && model[0] == ' ') model.erase(0, 1);
        if (!stare.empty() && stare[0] == ' ') stare.erase(0, 1);

        int id = std::stoi(id_str);
        int putere = std::stoi(putere_str);

        masini.push_back(Masina(id, model, putere, stare));
    }
    fin.close();
}

void Repo::saveToFile()
{
    std::ofstream fout(filename);
    for (const auto& m : masini)
    {
        fout << m.getId() << ", " << m.getModelMotor() << ", " << m.getPutere() << ", " << m.getStareECU() << "\n";
    }
    fout.close();
}

std::vector<Masina>& Repo::getAll()
{
    return masini;
}

void Repo::updateMasina(int id, int putereNoua, const std::string& stareNoua)
{
    for (auto& m : masini)
    {
        if (m.getId() == id)
        {
            m.setPutere(putereNoua);
            m.setStareECU(stareNoua);
            break;
        }
    }
    saveToFile();
}