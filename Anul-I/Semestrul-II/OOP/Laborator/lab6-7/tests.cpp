#include "tests.h"
#include "domain.h"
#include "validator.h"
#include "repository.h"
#include "service.h"
#include <assert.h>
#include <sstream>

void tests_vector() {
	VectorDinamic<int> v;
	assert(v.size() == 0);

	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	assert(v.size() == 3);
	assert(v.at(0) == 10);
	assert(v.at(2) == 30);

	try {
		v.at(5);
		assert(false);
	}
	catch (const std::out_of_range&) {
		assert(true);
	}

	v.erase(1);
	assert(v.size() == 2);
	assert(v.at(0) == 10);
	assert(v.at(1) == 30);

	VectorDinamic<int> v_copy = v;
	assert(v_copy.size() == 2);
	assert(v_copy.at(1) == 30);

	v_copy.at(0) = 99;
	assert(v.at(0) == 10);

	VectorDinamic<int> v_moved = std::move(v_copy);
	assert(v_moved.size() == 2);
	assert(v_copy.size() == 0);

	VectorDinamic<int> v_assigned;
	v_assigned = v;
	assert(v_assigned.size() == 2);
	assert(v_assigned.at(0) == 10);

	VectorDinamic<int> v_move_assigned;
	v_move_assigned = std::move(v_assigned);
	assert(v_move_assigned.size() == 2);
	assert(v_assigned.size() == 0);

	std::cout << "Trecut vector dinamic\n";
}

void tests_domain() {
	Activitate a = Activitate("Titlu", "Descriere", "Tip", 10);
	assert(a.get_titlu() == "Titlu");
	assert(a.get_descriere() == "Descriere");
	assert(a.get_tip() == "Tip");
	assert(a.get_durata() == 10);

	a.set_titlu("Titlu2");
	a.set_descriere("Descriere2");
	a.set_tip("Tip2");
	a.set_durata(20);

	assert(a.get_titlu() == "Titlu2");
	assert(a.get_descriere() == "Descriere2");
	assert(a.get_tip() == "Tip2");
	assert(a.get_durata() == 20);

	Activitate a2{ "Titlu2", "AltaDescriere", "Tip2", 30 };
	assert(a == a2);

	Activitate a3{ "Titlu3", "Desc", "Tip3", 10 };
	assert(!(a == a3));

	Activitate a_out = Activitate("Titlu", "Descriere", "Tip", 10);
	std::stringstream out;
	out << a_out;
	const std::string output = out.str();
	assert(output == "Activitate: [ Titlu: Titlu, Descriere: Descriere, Tip: Tip, Durata: 10 minute ]");
	std::cout << "Trecut domain\n";
}

void tests_validator() {
	Activitate a;
	Validator val;
	try {
		val.validate(a);
		assert(false);
	}
	catch (const ValidationException& e) {
		assert(e.get_msg() != "");
	}
	a = Activitate("Titlu", "Descriere", "Tip", 10);
	try {
		val.validate(a);
		assert(true);
	}
	catch (const ValidationException&) {
		assert(false);
	}
	std::cout << "Trecut validator\n";
}

void tests_repo() {
	Repository repo;
	assert(repo.repo_get_all().size() == 0);
	Activitate a = Activitate("Titlu", "Descriere", "Tip", 10);
	try {
		repo.repo_add(a);
		assert(true);
	}
	catch (const RepoException&) {
		assert(false);
	}
	try {
		repo.repo_add(a);
		assert(false);
	}
	catch (const RepoException& e) {
		assert(e.get_msg() != "");
	}
	assert(repo.repo_get_all().size() == 1);

	assert(repo.repo_search("Titlu", "Tip") == 0);
	assert(repo.repo_search("Titlu", "Tip2") == -1);

	assert(repo.repo_get_activitate(0) == a);

	try {
		repo.repo_delete("Titlu", "Tip");
		assert(true);
	}
	catch (const RepoException&) {
		assert(false);
	}
	try {
		repo.repo_delete("Titlu", "Tip");
		assert(false);
	}
	catch (const RepoException&) {
		assert(true);
	}

	assert(repo.repo_get_all().size() == 0);

	repo.repo_add(a);
	Activitate a_new = Activitate("Titlu", "DescNew", "Tip", 20);
	try {
		repo.repo_update(a_new);
		assert(true);
	}
	catch (const RepoException&) {
		assert(false);
	}
	assert(repo.repo_get_activitate(0) == a_new);
	a_new.set_tip("Tip2");
	try {
		repo.repo_update(a_new);
		assert(false);
	}
	catch (const RepoException&) {
		assert(true);
	}

	std::cout << "Trecut repo\n";
}

void tests_service() {
	Repository repo;
	Validator val;
	Service srv = Service(repo, val);
	//test adaugare element invalid
	try {
		srv.srv_add("", "", "", 0);
		assert(false);
	}
	catch (const ValidationException&) {
		assert(true);
	}
	catch (const RepoException&) {
		assert(false);
	}
	//test adaugare elem valid
	try {
		srv.srv_add("Titlu", "Descriere", "Tip", 10);
		assert(true);
	}
	catch (const ValidationException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}
	//test adaugare elem existent
	try {
		srv.srv_add("Titlu", "Descriere", "Tip", 10);
		assert(false);
	}
	catch (const ValidationException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(true);
	}

	assert(srv.srv_get_all().size() == 1);

	assert(srv.srv_search("Titlu", "Tip") == Activitate("Titlu", "Descriere", "Tip", 10));
	//test cautare elem inexistent
	try {
		srv.srv_search("Titlu2", "Tip2");
		assert(false);
	}
	catch (const ValidationException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(true);
	}

	//test update elem valid si existent
	try {
		srv.srv_update("Titlu", "DescNew", "Tip", 20);
		assert(true);
	}
	catch (const ValidationException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}
	//test update elem valid dar inexistent
	try {
		srv.srv_update("Titlu2", "DescNew", "Tip2", 20);
		assert(false);
	}
	catch (const ValidationException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(true);
	}
	//test update elem invalid
	try {
		srv.srv_update("", "", "", 0);
		assert(false);
	}
	catch (const ValidationException&) {
		assert(true);
	}
	catch (const RepoException&) {
		assert(false);
	}

	assert(srv.srv_search("Titlu", "Tip") == Activitate("Titlu", "DescNew", "Tip", 20));
	//test stergere elem existent
	try {
		srv.srv_delete("Titlu", "Tip");
		assert(true);
	}
	catch (const ValidationException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}
	//test stergere elem inexistent
	try {
		srv.srv_delete("Titlu", "Tip");
		assert(false);
	}
	catch (const ValidationException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(true);
	}
	
	assert(srv.srv_get_all().size() == 0);

	//teste filtrari
	Activitate a1 = Activitate("Titlu1", "Descriere1", "Tip1", 10);
	Activitate a2 = Activitate("Titlu2", "Descriere2", "Tip2", 10);
	srv.srv_add(a1.get_titlu(), a1.get_descriere(), a1.get_tip(), a1.get_durata());
	srv.srv_add(a2.get_titlu(), a2.get_descriere(), a2.get_tip(), a2.get_durata());


	auto dto_desc = srv.srv_filtrare_desc("Descriere1");
	assert(dto_desc.size() == 1);
	assert(dto_desc.at(0) == a1);
	dto_desc = srv.srv_filtrare_desc("Descriere2");
	assert(dto_desc.size() == 1);
	assert(dto_desc.at(0) == a2);
	dto_desc = srv.srv_filtrare_desc("Descriere3");
	assert(dto_desc.size() == 0);

	auto dto_tip = srv.srv_filtrare_tip("Tip1");
	assert(dto_tip.size() == 1);
	assert(dto_tip.at(0) == a1);
	dto_tip = srv.srv_filtrare_tip("Tip2");
	assert(dto_tip.size() == 1);
	assert(dto_tip.at(0) == a2);
	dto_tip = srv.srv_filtrare_tip("Tip3");
	assert(dto_tip.size() == 0);

	//teste sortari
	srv.srv_delete("Titlu1", "Tip1");
	srv.srv_delete("Titlu2", "Tip2");

	srv.srv_add("Z_Titlu", "B_Desc", "Sport", 60);
	srv.srv_add("A_Titlu", "A_Desc", "Hobby", 30);
	srv.srv_add("M_Titlu", "C_Desc", "Hobby", 90);

	// sortare dupa titlu
	auto sort_titlu = srv.srv_sort_titlu();
	assert(sort_titlu.at(0).get_titlu() == "A_Titlu");
	assert(sort_titlu.at(1).get_titlu() == "M_Titlu");
	assert(sort_titlu.at(2).get_titlu() == "Z_Titlu");

	// sortare dupa descriere
	auto sort_desc = srv.srv_sort_desc();
	assert(sort_desc.at(0).get_descriere() == "A_Desc");
	assert(sort_desc.at(1).get_descriere() == "B_Desc");
	assert(sort_desc.at(2).get_descriere() == "C_Desc");

	// sortare dupa tip si durata
	auto sort_compus = srv.srv_sort_tip_durata();
	assert(sort_compus.at(0).get_titlu() == "A_Titlu");
	assert(sort_compus.at(1).get_titlu() == "M_Titlu");
	assert(sort_compus.at(2).get_titlu() == "Z_Titlu");

	std::cout << "Trecut service\n";
}

void test_all() {
	tests_vector();
	tests_domain();
	tests_validator();
	tests_repo();
	tests_service();
}