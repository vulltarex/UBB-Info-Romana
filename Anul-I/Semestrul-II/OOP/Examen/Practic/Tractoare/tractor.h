#pragma once
#include <string>

class Tractor {
private:
    int id;
    std::string denumire;
    std::string tip;
    int numarRoti;
public:
    Tractor(int id, const std::string& denumire, const std::string& tip, int numarRoti) : id{ id }, denumire{ denumire }, tip { tip }, numarRoti { numarRoti } {}
    int getId() const { return id; }
    int getNumarRoti() const { return numarRoti; }
    const std::string& getDenumire() const { return denumire;}
    const std::string& getTip() const { return tip; }
};