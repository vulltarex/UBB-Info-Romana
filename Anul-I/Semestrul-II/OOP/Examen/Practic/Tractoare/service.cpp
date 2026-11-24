#include "service.h"

void Service::srvAdd(int id, const std::string& denumire, const std::string& tip, int numarRoti) {
    Tractor t {id, denumire, tip, numarRoti};
    val.validate(t);
    repo.repoAdd(t);
}

const std::vector<Tractor>& Service::srvGetAll() const {
    return repo.repoGetAll();
}