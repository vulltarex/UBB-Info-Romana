#pragma once
#include "student.h"
#include <vector>

class Repo {
private:
    std::string filename;
    std::vector<Student> studenti;
    void loadFromFile();
    void saveToFile();
public:
    /* Creeaza o instanta repo cu acces la fisierul dat ca parametru
     * pre: filename - string nevid ce contine un fisier valid;
     * post: este creata o instanta repo cu acces la fisierul cu numele furnizat
     */
    Repo(const std::string& filename);
    /* Sterge studentul cu id-ul furnizat ca parametru
     * pre: id - intreg valid ce reprezinta id-ul unui student stocat
     * post: studentul cu id-ul dat se sterge din repo si din fisier
     */
    void repoDelete(int id);
    /* Studentului cu id-ul dat i se actualizeaza varsta cu cea data ca parametru
     * pre: id - intreg reprezentand id-ul unui student stocat
     *      varstaNoua - intreg valid ce reprezinta varsta actualizata
     * post: varsta studentului este actualizata cu modificarile salvate in fisier
     */
    void repoUpdate(int id, int varstaNoua);
    /* Returneaza o referinta catre vectorul de studenti stocati in repo
     * post: este returnata o referinta valida catre vectorul de studenti stocati
     */
    std::vector<Student>& getAll();
    void repoUndo(std::vector<Student> stare);
};