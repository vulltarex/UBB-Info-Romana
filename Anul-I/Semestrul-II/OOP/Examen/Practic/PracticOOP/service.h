#pragma once
#include "repo.h"
class Service {
private:
    Repo& repo;
    std::vector<std::vector<Student>> stariUndo;
    std::vector<std::vector<Student>> stariRedo;
public:
    /* Creeaza o instanta valida Service cu acces la repo-ul dat ca parametru
     * pre: repo - instanta repo valida
     * post: este creata o instanta service valida cu acces la repo-ul furnizat
     */
    Service(Repo& repo) : repo(repo) {}
    /* Sterge din fisier studentul cu id-ul dat ca parametru
     * pre: id - intreg ce reprezinta un numar matricol valid al unui student stocat
     * post: studentul cu id-ul furnizat este sters din repo si fisier
     */
    void srvDelete(int id) { repo.repoDelete(id); }
    /* Incrementeaza varsta tututor studentilor stocati
     * post: se incrementeaza varsta tuturor studentilor in repo si fisier
     */
    void srvInc() {
        std::vector<Student> stareUndo;
        for (const auto s : srvGetAll()) stareUndo.push_back(s);
        stariUndo.push_back(stareUndo);
        for (const auto& s : repo.getAll()) {
            repo.repoUpdate(s.getNrMatricol(), s.getVarsta() + 1);
        }
        std::vector<Student> stareRedo;
        for (const auto s : srvGetAll()) stareUndo.push_back(s);
        stariUndo.push_back(stareRedo);
    }
    /* Decrementeaza varsta tututor studentilor stocati
     * post: se decrementeaza varsta tuturor studentilor in repo si fisier
     */
    void srvDec() {
        std::vector<Student> stareUndo;
        for (const auto s : srvGetAll()) stareUndo.push_back(s);
        stariUndo.push_back(stareUndo);
        for (const auto& s : repo.getAll()) {
            repo.repoUpdate(s.getNrMatricol(), s.getVarsta() - 1);
        }
        std::vector<Student> stareRedo;
        for (const auto s : srvGetAll()) stareUndo.push_back(s);
        stariUndo.push_back(stareRedo);
    }
    /* Returneaza un vector ce contine toti studentii, sortati crescator dupa varsta
     * post: este returnat un vector sortat crescator dupa varsta, continand toti studentii
     */
    std::vector<Student> srvGetAll() {
        std::vector<Student> dto;
        for (const auto s : repo.getAll())
            dto.push_back(s);
        std::sort(dto.begin(), dto.end(), [&](const auto& a, const auto& b) {
           return a.getVarsta() < b.getVarsta();
        });
        return dto;
    }

    void undo() {
        if (stariUndo.empty()) throw std::runtime_error("Nu mai exista operatii!");
        repo.repoUndo(stariUndo.back());
        stariUndo.pop_back();
    }
};