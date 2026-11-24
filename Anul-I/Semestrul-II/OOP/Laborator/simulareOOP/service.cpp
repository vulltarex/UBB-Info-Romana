#include "service.h"
#include <algorithm>
#include <iterator>

const std::vector<Instrument> Service::srvFilterBrand(const std::string& brand) const {
    std::vector<Instrument> dto;
    std::copy_if(repo.repoGetAll().begin(), repo.repoGetAll().end(), std::back_inserter(dto), [&brand](const Instrument& i) {
        return i.getBrand() == brand;
        });
    return dto;
}

const std::vector<Instrument> Service::srvFilterCod(int cod) const {
    std::vector<Instrument> dto;
    std::copy_if(repo.repoGetAll().begin(), repo.repoGetAll().end(), std::back_inserter(dto), [&](const Instrument& i) {
        return i.getCod() == cod;
        });
    return dto;
}

const std::vector<Instrument>& Service::srvGetAll() const {
    return repo.repoGetAll();
}
