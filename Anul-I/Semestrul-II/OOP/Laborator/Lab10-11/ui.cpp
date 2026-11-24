#include "ui.h"
#include <fstream>
using std::cout;
using std::cin;

Console::Console(Service& srv) noexcept : srv{ srv } {};

static int citire_int(const std::string& mesaj) {
	int val = 0;
	while (true) {
		cout << mesaj;
		if (!(cin >> val)) {
			cin.clear();
			while (cin.get() != '\n');
			cout << "Introduceti un numar intreg!\n";
		}
		else {
			while (cin.get() != '\n');
			return val;
		}
	}
}
static void print_menu() {
	cout << "1. Adaugare activitate\n";
	cout << "2. Stergere activitate\n";
	cout << "3. Modificare activitate\n";
	cout << "4. Cautare activitate\n";
	cout << "5. Afisare activitati\n";
	cout << "6. Filtrare activitati\n";
	cout << "7. Sortare activitati\n";
	cout << "8. Golire lista activitati\n";
	cout << "9. Adaugare dupa titlu\n";
	cout << "10. Generare lista activitati\n";
	cout << "11. Export\n";
	cout << "12. Afisare raport\n";
	cout << "13. Undo\n";
	cout << "0. Iesire\n";
}

void Console::ui_add() {
	std::string titlu, descriere, tip;
	int durata;
	cout << "Introduceti titlul activitatii: ";
	getline(cin, titlu);
	cout << "Introduceti descrierea activitatii: ";
	getline(cin, descriere);
	cout << "Introduceti tipul activitatii: ";
	getline(cin, tip);
	durata = citire_int("Introduceti durata activitatii: ");
	try {
		srv.srv_add(titlu, descriere, tip, durata);
		cout << "Activitate adaugata!\n";
	}
	catch (const RepoException& e) {
		cout << e.get_msg();
	}
	catch (const ValidationException& e) {
		cout << e.get_msg();
	}
}

void Console::ui_delete() {
	std::string titlu, tip;
	cout << "Introduceti titlul activitatii: ";
	getline(cin, titlu);
	cout << "Introduceti tipul activitatii: ";
	getline(cin, tip);
	try {
		srv.srv_delete(titlu, tip);
		cout << "Activitate stearsa!\n";
	}
	catch (const RepoException& e) {
		cout << e.get_msg();
	}
}

void Console::ui_update() {
	std::string titlu, descriere_noua, tip;
	int durata_noua;
	cout << "Introduceti titlul activitatii de modificat: ";
	getline(cin, titlu);
	cout << "Introduceti tipul activitatii de modificat: ";
	getline(cin, tip);
	cout << "Introduceti noua descriere: ";
	getline(cin, descriere_noua);
	durata_noua = citire_int("Introduceti noua durata: ");
	try {
		srv.srv_update(titlu, descriere_noua, tip, durata_noua);
		cout << "Activitate modificata!\n";
	}
	catch (const RepoException& e) {
		cout << e.get_msg();
	}
	catch (const ValidationException& e) {
		cout << e.get_msg();
	}
}

void Console::ui_search() const {
	std::string titlu, tip;
	cout << "Introduceti titlul activitatii cautate: ";
	getline(cin, titlu);
	cout << "Introduceti tipul activitatii cautate: ";
	getline(cin, tip);
	try {
		const Activitate& a = srv.srv_search(titlu, tip);
		cout << a << '\n';
	}
	catch (const RepoException& e) {
		cout << e.get_msg();
	}
}

void Console::ui_show_all() const {
	try {
		const std::vector<Activitate> activitati = srv.srv_get_all();
		if (activitati.size() == 0) {
			cout << "Nu exista activitati!\n";
			return;
		}
		for (const Activitate& a : activitati) {
			cout << a << '\n';
		}
	}
	catch (const RepoException& e) {
		cout << e.get_msg();
	}
}

void Console::ui_filtrare() const {
	cout << "1. Filtrare dupa descriere\n";
	cout << "2. Filtrare dupa tip\n";
	const int cmd = citire_int("Alegeti tipul de filtrare: ");
	switch (cmd) {
	case 1: {
		std::string descriere;
		cout << "Introduceti descrierea cautata: ";
		getline(cin, descriere);
		try {
			const auto dto = srv.srv_filtrare_desc(descriere);
			for (const Activitate& a : dto) {
				cout << a << '\n';
			}
		}
		catch (const RepoException& e) {
			cout << e.get_msg();
		}
		break;
	}
	case 2: {
		std::string tip;
		cout << "Introduceti tipul cautat: ";
		getline(cin, tip);
		try {
			const auto dto = srv.srv_filtrare_tip(tip);
			for (const Activitate& a : dto) {
				cout << a << '\n';
			}
		}
		catch (const RepoException& e) {
			cout << e.get_msg();
		}
		
		break;
	}
	default: {
		cout << "Introduceti o comanda valida!\n";
		ui_filtrare();
		break;
	}
	}
}

void Console::ui_sortare() const {
	cout << "1. Sortare dupa titlu\n";
	cout << "2. Sortare dupa descriere\n";
	cout << "3. Sortare dupa tip si durata\n";
	const int cmd = citire_int("Alegeti tipul de sortare: ");
	switch (cmd) {
	case 1: {
		try {
			std::vector<Activitate> rez = srv.srv_sort_titlu();
			for (const Activitate& a : rez) {
				cout << a << '\n';
			}
		}
		catch (const RepoException& e) {
			cout << e.get_msg();
		}
		
		break;
	}
	case 2: {
		try {
			std::vector<Activitate> rez = srv.srv_sort_desc();
			for (const Activitate& a : rez) {
				cout << a << '\n';
			}
		}
		catch (const RepoException& e) {
			cout << e.get_msg();
		}
		
		break;
	}
	case 3: {
		try {
			std::vector<Activitate> rez = srv.srv_sort_tip_durata();
			for (const Activitate& a : rez) {
				cout << a << '\n';
			}
		}
		catch (const RepoException& e) {
			cout << e.get_msg();
		}
		
		break;
	}
	default: {
		cout << "Introduceti o comanda valida!\n";
		ui_sortare();
		break;
	}
	}
}

void Console::ui_print_list_size() const {
	cout << "Numarul activitatilor din lista: " << srv.srv_get_list_size() << '\n';
}

void Console::ui_clear_list() {
	srv.srv_clear_list();
	cout << "Lista a fost golita!\n";
	ui_print_list_size();
}

void Console::ui_add_to_list() {
	std::string titlu;
	cout << "Introduceti titlul activitatii de adaugat: ";
	getline(cin, titlu);
	try {
		srv.srv_add_to_list(titlu);
		cout << "Activitate adaugata in lista!\n";
		ui_print_list_size();
	}
	catch (const ServiceException& e) {
		cout << e.get_msg();
	}
	catch (const RepoException& e) {
		cout << e.get_msg();
	}
}

void Console::ui_generate_list() {
	const int count = citire_int("Introduceti numarul de activitati: ");
	try {
		srv.srv_generate_list(count);
		cout << "Lista generata cu succes!\n";
		ui_print_list_size();
	}
	catch (const ServiceException& e) {
		cout << e.get_msg();
	}
	catch (const RepoException& e) {
		cout << e.get_msg();
	}
}

void Console::ui_export_list() const {
	std::string filename;
	cout << "Introduceti numele fisierului (extensii admise .csv si .html): ";
	getline(cin, filename);
	try {
		srv.srv_export_list(filename);
		cout << "Lista exportata cu succes!\n";
	}
	catch (const ServiceException& e) {
		cout << e.get_msg();
	}
	catch (const ListException& e) {
		cout << e.get_msg();
	}
	catch (const RepoException& e) {
		cout << e.get_msg();
	}
}

void Console::ui_afisare_raport() const {
	try {
		const std::map<std::string, int> r = srv.srv_creare_raport();
		for (const auto& e : r) {
			cout << e.second << " activitati de tipul " << e.first << '\n';
		}
	}
	catch (const RepoException& e) {
		cout << e.get_msg();
	}
}

void Console::ui_undo() {
	try {
		srv.srv_undo();
		cout << "Undo realizat cu succes!\n";
	}
	catch (const ServiceException& e) {
		cout << e.get_msg();
	}
}

void Console::run() {
	bool ruleaza = true;
	while (ruleaza) {
		print_menu();
		const int cmd = citire_int("Introduceti o comanda: ");
		switch (cmd) {
		case 1: {
			ui_add();
			break;
		}
		case 2: {
			ui_delete();
			break;
		}
		case 3: {
			ui_update();
			break;
		}
		case 4: {
			ui_search();
			break;
		}
		case 5: {
			ui_show_all();
			break;
		}
		case 6: {
			ui_filtrare();
			break;
		}
		case 7: {
			ui_sortare();
			break;
		}
		case 8: {
			ui_clear_list();
			break;
		}
		case 9: {
			ui_add_to_list();
			break;
		}
		case 10: {
			ui_generate_list();
			break;
		}
		case 11: {
			ui_export_list();
			break;
		}
		case 12: {
			ui_afisare_raport();
			break;
		}
		case 13: {
			ui_undo();
			break;
		}
		case 0: {
			ruleaza = false;
			break;
		}
		default: {
			cout << "Introduceti o comanda valida!\n";
			break;
		}
		}
	}
}