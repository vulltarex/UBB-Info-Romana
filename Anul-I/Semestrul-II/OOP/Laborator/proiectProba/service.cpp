#include "service.h"
#include <algorithm>

const std::vector<Masina> Service::srvSort() const {
	std::vector<Masina> dto = std::copy(repo.repoGetAll().begin(), repo.repoGetAll().end(), dto);
	std::sort(dto.begin(), dto.end(), [&](const int varsta1, const int varsta2) {
		return varsta1 < varsta2;
		});
	return dto;
}

const std::vector<Masina> Service::srvFilter(const std::string& specie) const {
	std::vector<Masina> dto = std::copy_if(repo.repoGetAll().begin(), repo.repoGetAll().end(), dto, [&](const Masina& m, const std::string& specie) {
		return 	m.getSpecie() == specie;
	});
	return dto;
}

const std::vector<Masina>& Service::srvGetAll() const {
	return repo.repoGetAll();
}
