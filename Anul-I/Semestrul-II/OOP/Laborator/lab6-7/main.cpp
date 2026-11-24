#include "ui.h"
#include "tests.h"

#define _CRTDBG_MAP_ALLOC

int main() {
	test_all();
	std::cout << "Toate testele au trecut!\n";
	if (_CrtDumpMemoryLeaks() == 1) {
		std::cout << "Exista memory leak!\n";
	}
	else {
		std::cout << "Nu exista memory leak!\n";
	}

	Validator val;
	Repository repo;
	Service srv(repo, val);
	Console ui(srv);

	srv.srv_add("Lab OOP", "Laborator C++ despre clase si obiecte", "Facultate", 120);
	srv.srv_add("Sala", "Antrenament full body", "Sport", 45);
	srv.srv_add("Ping-Pong", "Meciuri de tenis de masa", "Hobby", 100);
	srv.srv_add("Cumparaturi", "Mancare pentru saptamana viitoare", "Personal", 60);
	srv.srv_add("Culcare", "Un somn odihnitor", "Personal", 4);

	ui.run();

	return 0;
}