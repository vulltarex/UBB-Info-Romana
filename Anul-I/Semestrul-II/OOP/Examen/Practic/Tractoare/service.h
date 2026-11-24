#pragma once
#include "repository.h"
#include "validator.h"

class Service {
private:
    Validator& val;
    Repo& repo;
public:
    Service(Validator& val, Repo& repo) : val{ val }, repo{ repo } {}
    void srvAdd(int id, const std::string& denumire, const std::string& tip, int numarRoti);
    const std::vector<Tractor>& srvGetAll() const;
};