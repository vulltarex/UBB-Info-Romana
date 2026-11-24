#pragma once
#include <string>

class Student {
private:
    int nrMatricol;
    std::string nume;
    int varsta;
    std::string facultate;
public:
    /* Creeaza o instanta student cu atributele date ca parametru
     * pre: nrmatricol - intreg reprezentand numarul matricol al studentului
     *      nume - string nevid reprezentand numele studentului
     *      varsta - intreg reprezentand varsta studentului
     *      facultate - string reprezentand facultatea la care studiaza studentul
     *      poate fi "mate", "info", "mate-info" sau "ai"
     * post: este creata o instanta student valida, cu atributele furnizate
     */
    Student(int nrmatricol, const std::string& nume, int varsta, const std::string& facultate)
        : nrMatricol(nrmatricol), nume(nume), varsta(varsta), facultate(facultate) {}
    /* Returneaza numarul matricol al studentului
     * post: este returnat numarul matricol al studentului
     */
    int getNrMatricol() const { return nrMatricol; }
    /* Returneaza numele studentului
     * post: este returnat numele studentului
     */
    const std::string& getNume() const { return nume; }
    /* Returneaza varsta studentului
     * post: este returnata varsta studentului
     */
    int getVarsta() const { return varsta; }
    /* Returneaza facultatea studentului
     * post: este returnata facultatea studentului
     */
    const std::string& getFacultate() const { return facultate; }
    /* Actualizeaza varsta studentului
     * pre: varstaNoua - intreg reprezentand noua varsta a studentului
     * post: este actualizata varsta studentului
     */
    void setVarsta(int varstaNoua) {
        varsta = varstaNoua;
    }
};