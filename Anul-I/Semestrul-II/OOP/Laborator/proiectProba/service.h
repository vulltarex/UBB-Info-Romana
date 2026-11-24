#pragma once
#include "repo.h"
class Service {
private:
	Repo& repo;
public:
	Service(Repo& repo) : repo{ repo } {}
	const std::vector<Masina> srvSort() const;
	const std::vector<Masina> srvFilter() const;
	const std::vector<Masina>& srvGetAll() const;
};