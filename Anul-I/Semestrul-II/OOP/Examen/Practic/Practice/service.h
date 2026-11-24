#pragma once
#include "repo.h"

class Service
{
private:
    Repo& repo;

public:
    Service(Repo& repo);
    std::vector<Masina>& getAll();
    void aplicaStage1(int id);
};