#include "Service.h"

Service::Service(Repo& repo) : repo(repo)
{
}

std::vector<Masina>& Service::getAll()
{
    return repo.getAll();
}

void Service::aplicaStage1(int id)
{
    for (auto& m : repo.getAll())
    {
        if (m.getId() == id && m.getStareECU() == "stoc")
        {
            repo.updateMasina(id, m.getPutere() + 30, "stage1");
            break;
        }
    }
}