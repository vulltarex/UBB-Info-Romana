#include "tests.h"
#include <assert.h>
#include <fstream>

void testInstrument() {
	Instrument i{ 1, "Tip", "Brand", 5 };
	assert(i.getCod() == 1);
	assert(i.getTip() == "Tip");
	assert(i.getBrand() == "Brand");
	assert(i.getConsumEnergetic() == 5);
}

void testRepoService() {
	std::ofstream fout("test.txt");
	fout << "1,Tip1,Brand1,100\n";
	fout << "2,Tip2,Brand2,200\n";
	fout << "3,Tip3,Brand3,300\n";
	fout.close();
	Repo repo("test.txt");
	assert(repo.repoGetAll().size() == 3);
	assert(repo.repoGetAll().at(0).getCod() == 1);
	assert(repo.repoGetAll().at(1).getCod() == 2);
	assert(repo.repoGetAll().at(2).getCod() == 3);

	Service srv(repo);
	assert(srv.srvGetAll().at(0).getCod() == 1);
	assert(srv.srvGetAll().at(1).getCod() == 2);
	assert(srv.srvGetAll().at(2).getCod() == 3);

	assert(srv.srvFilterBrand("Brand1").size() == 1);
	assert(srv.srvFilterBrand("Brand1").at(0).getCod() == 1);
	assert(srv.srvFilterBrand("Brand").size() == 0);

	assert(srv.srvFilterCod(1).size() == 1);
	assert(srv.srvFilterCod(1).at(0).getCod() == 1);
	assert(srv.srvFilterCod(0).size() == 0);
}
