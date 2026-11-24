#pragma once
#include <string>

class Masina {
private:
    int id;
    std::string modelMotor;
    int putere;
    std::string stareECU;
public:
    Masina(int id, const std::string& modelMotor, int putere, const std::string& stareECU) : id(id), modelMotor(modelMotor), putere(putere), stareECU(stareECU) {}
    int getId() const { return id; }
    const std::string& getModelMotor() const { return modelMotor; }
    int getPutere() const { return putere; }
    const std::string& getStareECU() const { return stareECU; }
    void setPutere(int p) { putere = p; }
    void setStareECU(const std::string& s) { stareECU = s; }
};
