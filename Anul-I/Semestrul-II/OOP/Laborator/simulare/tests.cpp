#include "tests.h"
#include <fstream>
#include <iostream>

void testAutomobil() {
	Automobil a{ 1, "Nume", "Tip", 300 };
	assert(a.getCod() == 1);
	assert(a.getDenumire() == "Nume");
	assert(a.getTip() == "Tip");
	assert(a.getNecesarApa() == 300);
	std::cout << "trecut automobil";
}

void testRepoService() {
	std::ofstream fout("teste.txt");
	fout << "1,Nume1,Tip1,300\n";
	fout << "2,Nume2,Tip2,301\n";
	fout << "3,Nume3,Tip3,302\n";
	fout.close();
	Repo repo("teste.txt");
	assert(repo.repoGetAll().at(0).getCod() == 1);
	assert(repo.repoGetAll().at(0).getDenumire() == "Nume1");
	assert(repo.repoGetAll().at(0).getTip() == "Tip1");
	assert(repo.repoGetAll().at(0).getNecesarApa() == 300);

	assert(repo.repoGetAll().at(1).getCod() == 2);
	assert(repo.repoGetAll().at(1).getDenumire() == "Nume2");
	assert(repo.repoGetAll().at(1).getTip() == "Tip2");
	assert(repo.repoGetAll().at(1).getNecesarApa() == 301);

	assert(repo.repoGetAll().at(2).getCod() == 3);
	assert(repo.repoGetAll().at(2).getDenumire() == "Nume3");
	assert(repo.repoGetAll().at(2).getTip() == "Tip3");
	assert(repo.repoGetAll().at(2).getNecesarApa() == 302);

	Service srv(repo);

	assert(srv.srvSortTip(repo.repoGetAll()).at(0).getCod() == 1);
	assert(srv.srvSortTip(repo.repoGetAll()).at(1).getCod() == 2);

	assert(srv.srvFilterNecesarApa(repo.repoGetAll(), 300).size() == 0);
	assert(srv.srvFilterNecesarApa(repo.repoGetAll(), 301).size() == 1);
	assert(srv.srvFilterNecesarApa(repo.repoGetAll(), 301).at(0).getCod() == 1);

	assert(srv.srvGetAll().at(0).getCod() == repo.repoGetAll().at(0).getCod());
	assert(srv.srvGetAll().at(1).getCod() == repo.repoGetAll().at(1).getCod());
	assert(srv.srvGetAll().at(2).getCod() == repo.repoGetAll().at(2).getCod());
}