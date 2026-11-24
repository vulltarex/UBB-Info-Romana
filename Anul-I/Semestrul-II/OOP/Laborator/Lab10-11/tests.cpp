//#include "tests.h"
//#include "activitate.h"
//#include "validator.h"
//#include "repository.h"
//#include "service.h"
//#include <assert.h>
//#include <sstream>
//
////void tests_vector() {
////	std::vector<int> v;
////	assert(v.size() == 0);
////
////	v.push_back(10);
////	v.push_back(20);
////	v.push_back(30);
////	assert(v.size() == 3);
////	assert(v.at(0) == 10);
////	assert(v.at(2) == 30);
////
////	v.erase(v.begin() + 1);
////	assert(v.size() == 2);
////	assert(v.at(0) == 10);
////	assert(v.at(1) == 30);
////
////	std::vector<int> v_copy = v;
////	assert(v_copy.size() == 2);
////	assert(v_copy.at(1) == 30);
////
////	v_copy.at(0) = 99;
////	assert(v.at(0) == 10);
////
////	std::vector<int> v_moved = std::move(v_copy);
////	assert(v_moved.size() == 2);
////	assert(v_copy.size() == 0);
////
////	std::vector<int> v_assigned;
////	v_assigned = v;
////	assert(v_assigned.size() == 2);
////	assert(v_assigned.at(0) == 10);
////
////	std::vector<int> v_move_assigned;
////	v_move_assigned = std::move(v_assigned);
////	assert(v_move_assigned.size() == 2);
////	assert(v_assigned.size() == 0);
////
////	std::cout << "Trecut vector dinamic\n";
////}
//
//void tests_domain() {
//	Activitate a = Activitate("Titlu", "Descriere", "Tip", 10);
//	assert(a.get_titlu() == "Titlu");
//	assert(a.get_descriere() == "Descriere");
//	assert(a.get_tip() == "Tip");
//	assert(a.get_durata() == 10);
//
//	a.set_titlu("Titlu2");
//	a.set_descriere("Descriere2");
//	a.set_tip("Tip2");
//	a.set_durata(20);
//
//	assert(a.get_titlu() == "Titlu2");
//	assert(a.get_descriere() == "Descriere2");
//	assert(a.get_tip() == "Tip2");
//	assert(a.get_durata() == 20);
//
//	Activitate a2{ "Titlu2", "AltaDescriere", "Tip2", 30 };
//	assert(a == a2);
//
//	Activitate a3{ "Titlu3", "Desc", "Tip3", 10 };
//	assert(!(a == a3));
//
//	Activitate a_out = Activitate("Titlu", "Descriere", "Tip", 10);
//	std::stringstream out;
//	out << a_out;
//	const std::string output = out.str();
//	assert(output == "Activitate: [ Titlu: Titlu, Descriere: Descriere, Tip: Tip, Durata: 10 minute ]");
//	std::cout << "Trecut domain\n";
//}
//
//void tests_validator() {
//	Activitate a;
//	Validator val;
//	try {
//		val.validate(a);
//		assert(false);
//	}
//	catch (const ValidationException& e) {
//		assert(e.get_msg() != "");
//	}
//	a = Activitate("Titlu", "Descriere", "Tip", 10);
//	try {
//		val.validate(a);
//		assert(true);
//	}
//	catch (const ValidationException&) {
//		assert(false);
//	}
//	std::cout << "Trecut validator\n";
//}
//
//void tests_repo() {
//	Repository repo;
//	assert(repo.repo_get_all().size() == 0);
//	Activitate a = Activitate("Titlu", "Descriere", "Tip", 10);
//	try {
//		repo.repo_add(a);
//		assert(true);
//	}
//	catch (const RepoException&) {
//		assert(false);
//	}
//	try {
//		repo.repo_add(a);
//		assert(false);
//	}
//	catch (const RepoException& e) {
//		assert(e.get_msg() != "");
//	}
//	assert(repo.repo_get_all().size() == 1);
//
//	assert(repo.repo_search("Titlu", "Tip") == 0);
//	assert(repo.repo_search("Titlu", "Tip2") == -1);
//
//	assert(repo.repo_get_activitate(0) == a);
//
//	try {
//		repo.repo_delete("Titlu", "Tip");
//		assert(true);
//	}
//	catch (const RepoException&) {
//		assert(false);
//	}
//	try {
//		repo.repo_delete("Titlu", "Tip");
//		assert(false);
//	}
//	catch (const RepoException&) {
//		assert(true);
//	}
//
//	assert(repo.repo_get_all().size() == 0);
//
//	repo.repo_add(a);
//	Activitate a_new = Activitate("Titlu", "DescNew", "Tip", 20);
//	try {
//		repo.repo_update(a_new);
//		assert(true);
//	}
//	catch (const RepoException&) {
//		assert(false);
//	}
//	assert(repo.repo_get_activitate(0) == a_new);
//	a_new.set_tip("Tip2");
//	try {
//		repo.repo_update(a_new);
//		assert(false);
//	}
//	catch (const RepoException&) {
//		assert(true);
//	}
//
//	std::cout << "Trecut repo\n";
//}
//
//void tests_service() {
//	Repository repo;
//	Validator val;
//	ListaActivitati lista;
//	Service srv = Service(repo, val, lista);
//	//test adaugare element invalid
//	try {
//		srv.srv_add("", "", "", 0);
//		assert(false);
//	}
//	catch (const ValidationException&) {
//		assert(true);
//	}
//	catch (const RepoException&) {
//		assert(false);
//	}
//	//test adaugare elem valid
//	try {
//		srv.srv_add("Titlu", "Descriere", "Tip", 10);
//		assert(true);
//	}
//	catch (const ValidationException&) {
//		assert(false);
//	}
//	catch (const RepoException&) {
//		assert(false);
//	}
//	//test adaugare elem existent
//	try {
//		srv.srv_add("Titlu", "Descriere", "Tip", 10);
//		assert(false);
//	}
//	catch (const ValidationException&) {
//		assert(false);
//	}
//	catch (const RepoException&) {
//		assert(true);
//	}
//
//	assert(srv.srv_get_all().size() == 1);
//
//	assert(srv.srv_search("Titlu", "Tip") == Activitate("Titlu", "Descriere", "Tip", 10));
//	//test cautare elem inexistent
//	try {
//		srv.srv_search("Titlu2", "Tip2");
//		assert(false);
//	}
//	catch (const ValidationException&) {
//		assert(false);
//	}
//	catch (const RepoException&) {
//		assert(true);
//	}
//
//	//test update elem valid si existent
//	try {
//		srv.srv_update("Titlu", "DescNew", "Tip", 20);
//		assert(true);
//	}
//	catch (const ValidationException&) {
//		assert(false);
//	}
//	catch (const RepoException&) {
//		assert(false);
//	}
//	//test update elem valid dar inexistent
//	try {
//		srv.srv_update("Titlu2", "DescNew", "Tip2", 20);
//		assert(false);
//	}
//	catch (const ValidationException&) {
//		assert(false);
//	}
//	catch (const RepoException&) {
//		assert(true);
//	}
//	//test update elem invalid
//	try {
//		srv.srv_update("", "", "", 0);
//		assert(false);
//	}
//	catch (const ValidationException&) {
//		assert(true);
//	}
//	catch (const RepoException&) {
//		assert(false);
//	}
//
//	assert(srv.srv_search("Titlu", "Tip") == Activitate("Titlu", "DescNew", "Tip", 20));
//	//test stergere elem existent
//	try {
//		srv.srv_delete("Titlu", "Tip");
//		assert(true);
//	}
//	catch (const ValidationException&) {
//		assert(false);
//	}
//	catch (const RepoException&) {
//		assert(false);
//	}
//	//test stergere elem inexistent
//	try {
//		srv.srv_delete("Titlu", "Tip");
//		assert(false);
//	}
//	catch (const ValidationException&) {
//		assert(false);
//	}
//	catch (const RepoException&) {
//		assert(true);
//	}
//
//	assert(srv.srv_get_all().size() == 0);
//
//	//teste filtrari
//	Activitate a1 = Activitate("Titlu1", "Descriere1", "Tip1", 10);
//	Activitate a2 = Activitate("Titlu2", "Descriere2", "Tip2", 10);
//	srv.srv_add(a1.get_titlu(), a1.get_descriere(), a1.get_tip(), a1.get_durata());
//	srv.srv_add(a2.get_titlu(), a2.get_descriere(), a2.get_tip(), a2.get_durata());
//
//
//	const auto dto_desc1 = srv.srv_filtrare_desc("Descriere1");
//	assert(dto_desc1.size() == 1);
//	assert(dto_desc1.at(0) == a1);
//	const auto dto_desc2 = srv.srv_filtrare_desc("Descriere2");
//	assert(dto_desc2.size() == 1);
//	assert(dto_desc2.at(0) == a2);
//	const auto dto_desc3 = srv.srv_filtrare_desc("Descriere3");
//	assert(dto_desc3.size() == 0);
//
//	const auto dto_tip1 = srv.srv_filtrare_tip("Tip1");
//	assert(dto_tip1.size() == 1);
//	assert(dto_tip1.at(0) == a1);
//	const auto dto_tip2 = srv.srv_filtrare_tip("Tip2");
//	assert(dto_tip2.size() == 1);
//	assert(dto_tip2.at(0) == a2);
//	const auto dto_tip3 = srv.srv_filtrare_tip("Tip3");
//	assert(dto_tip3.size() == 0);
//
//	//teste sortari
//	srv.srv_delete("Titlu1", "Tip1");
//	srv.srv_delete("Titlu2", "Tip2");
//
//	srv.srv_add("Z_Titlu", "B_Desc", "Sport", 60);
//	srv.srv_add("A_Titlu", "A_Desc", "Hobby", 30);
//	srv.srv_add("M_Titlu", "C_Desc", "Hobby", 90);
//
//	// sortare dupa titlu
//	const auto sort_titlu = srv.srv_sort_titlu();
//	assert(sort_titlu.at(0).get_titlu() == "A_Titlu");
//	assert(sort_titlu.at(1).get_titlu() == "M_Titlu");
//	assert(sort_titlu.at(2).get_titlu() == "Z_Titlu");
//
//	// sortare dupa descriere
//	const auto sort_desc = srv.srv_sort_desc();
//	assert(sort_desc.at(0).get_descriere() == "A_Desc");
//	assert(sort_desc.at(1).get_descriere() == "B_Desc");
//	assert(sort_desc.at(2).get_descriere() == "C_Desc");
//
//	// sortare dupa tip si durata
//	const auto sort_compus = srv.srv_sort_tip_durata();
//	assert(sort_compus.at(0).get_titlu() == "A_Titlu");
//	assert(sort_compus.at(1).get_titlu() == "M_Titlu");
//	assert(sort_compus.at(2).get_titlu() == "Z_Titlu");
//
//	//teste lista
//
//	assert(srv.srv_get_list_size() == 0);
//
//	srv.srv_add("Titlu", "Descriere", "Tip", 10);
//	srv.srv_add_to_list("Titlu");
//	assert(srv.srv_get_list_size() == 1);
//	try {
//		srv.srv_add_to_list("");
//		assert(false);
//	}
//	catch (const ServiceException& e) {
//		assert(e.get_msg() != "");
//	}
//	srv.srv_clear_list();
//	assert(srv.srv_get_list_size() == 0);
//
//	try {
//		srv.srv_generate_list(6);
//		assert(false);
//	}
//	catch (const ServiceException&) {
//		assert(true);
//	}
//	try {
//		srv.srv_generate_list(1);
//		assert(true);
//	}
//	catch (const ServiceException&) {
//		assert(false);
//	}
//	try {
//		srv.srv_generate_list(1);
//		assert(true);
//	}
//	catch (const ServiceException&) {
//		assert(false);
//	}
//	assert(srv.srv_get_list_size() == 1);
//
//	try {
//		srv.srv_export_list("test");
//		assert(false);
//	}
//	catch (const ServiceException&) {
//		assert(true);
//	}
//	try {
//		srv.srv_export_list("test.csv");
//		assert(true);
//	}
//	catch (const ServiceException&) {
//		assert(false);
//	}
//	try {
//		srv.srv_export_list("test.html");
//		assert(true);
//	}
//	catch (const ServiceException&) {
//		assert(false);
//	}
//
//	try {
//		srv.srv_export_list("fisier_invalid_?*.csv");
//		assert(false);
//	}
//	catch (const ListException& e) {
//		assert(e.get_msg() != "");
//	}
//
//	try {
//		srv.srv_export_list("fisier_invalid_?*.html");
//		assert(false);
//	}
//	catch (const ListException&) {
//		assert(true);
//	}
//
//	std::cout << "Trecut service\n";
//}
//
//void tests_undo() {
//	Repository repo;
//	Validator val;
//	ListaActivitati lista;
//	Service srv(repo, val, lista);
//
//	// test pt zero operatii
//	try {
//		srv.srv_undo();
//		assert(false);
//	}
//	catch (const ServiceException& e) {
//		assert(e.get_msg() != "");
//	}
//
//	// teste pt undo adaugare
//	srv.srv_add("Titlu1", "Desc1", "Tip1", 10);
//	assert(srv.srv_get_all().size() == 1);
//	srv.srv_undo();
//	assert(srv.srv_get_all().size() == 0);
//
//	// teste pt undo stergere
//	srv.srv_add("Titlu1", "Desc1", "Tip1", 10);
//	srv.srv_delete("Titlu1", "Tip1");
//	assert(srv.srv_get_all().size() == 0);
//	srv.srv_undo();
//	assert(srv.srv_get_all().size() == 1);
//	assert(srv.srv_get_all().at(0).get_titlu() == "Titlu1");
//	assert(srv.srv_get_all().at(0).get_durata() == 10);
//
//	// teste pt undo modificare
//	srv.srv_update("Titlu1", "DescNou", "Tip1", 50);
//	assert(srv.srv_get_all().at(0).get_descriere() == "DescNou");
//	assert(srv.srv_get_all().at(0).get_durata() == 50);
//	srv.srv_undo();
//	assert(srv.srv_get_all().at(0).get_descriere() == "Desc1");
//	assert(srv.srv_get_all().at(0).get_durata() == 10);
//
//	//teste undo pt mai multe operatii
//	srv.srv_add("Titlu2", "Desc2", "Tip2", 20);
//	srv.srv_add("Titlu3", "Desc3", "Tip3", 30);
//	assert(srv.srv_get_all().size() == 3);
//
//	srv.srv_undo();
//	assert(srv.srv_get_all().size() == 2);
//	assert(srv.srv_get_all().at(1).get_titlu() == "Titlu2");
//
//	srv.srv_undo();
//	assert(srv.srv_get_all().size() == 1);
//	assert(srv.srv_get_all().at(0).get_titlu() == "Titlu1");
//
//	srv.srv_undo();
//	assert(srv.srv_get_all().size() == 0);
//
//	try {
//		srv.srv_undo();
//		assert(false);
//	}
//	catch (const ServiceException& e) {
//		assert(e.get_msg() != "");
//	}
//
//	std::cout << "Trecut undo\n";
//}
//
//void test_all() {
//	tests_domain();
//	tests_validator();
//	tests_repo();
//	tests_service();
//	tests_undo();
//}