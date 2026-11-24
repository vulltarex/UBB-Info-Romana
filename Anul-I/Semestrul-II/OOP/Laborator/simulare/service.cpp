#include "service.h"
#include <algorithm>
#include <iterator>

const std::vector<Automobil> Service::srvSortTip(const std::vector<Automobil>& all) const {
    std::vector<Automobil> dto(all.begin(), all.end());
    std::sort(dto.begin(), dto.end(), [&](const auto& a1, const auto& a2) {
        return a1.getTip() < a2.getTip();
        });
    return dto;
}

const std::vector<Automobil> Service::srvFilterNecesarApa(const std::vector<Automobil>& all, const int cantitate) const {
    std::vector<Automobil> dto;
    std::copy_if(all.begin(), all.end(), std::back_inserter(dto), [&](const Automobil& a) {
        return a.getNecesarApa() < cantitate;
        });
    return dto;
}

const std::vector<Automobil>& Service::srvGetAll() const {
    return repo.repoGetAll();
}
