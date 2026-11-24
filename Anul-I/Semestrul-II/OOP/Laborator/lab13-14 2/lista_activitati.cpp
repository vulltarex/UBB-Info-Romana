#include "lista_activitati.h"
#include <fstream>

void ListaActivitati::clear_list() noexcept {
	lista_activitati.clear();
	notify();
}

void ListaActivitati::add_to_list(const Activitate& a) {
	lista_activitati.push_back(a);
	notify();
}

void ListaActivitati::export_html(const std::string& filename) const {
	std::ofstream fout(filename);
	if (!fout.is_open()) {
		throw ListException("Eroare la deschiderea fisierului!\n");
	}
	fout << "<html><body>\n";
	fout << "<h1>Activitati Curente</h1>\n";
	fout << "<table border=\"1\">\n";
	fout << "<tr><th>Titlu</th><th>Descriere</th><th>Tip</th><th>Durata</th></tr>\n";

	for (const auto& a : lista_activitati) {
		fout << "<tr>";
		fout << "<td>" << a.get_titlu() << "</td>";
		fout << "<td>" << a.get_descriere() << "</td>";
		fout << "<td>" << a.get_tip() << "</td>";
		fout << "<td>" << a.get_durata() << "</td>";
		fout << "</tr>\n";
	}

	fout << "</table>\n";
	fout << "</body></html>\n";

	fout.close();
}

void ListaActivitati::export_csv(const std::string& filename) const {
	std::ofstream fout(filename);
	if (!fout.is_open()) {
		throw ListException("Eroare la deschiderea fisierului!\n");
	}
	fout << "Titlu,Descriere,Tip,Durata\n";
	for (const auto& act : lista_activitati) {
		fout << act.get_titlu() << ','
			<< act.get_descriere() << ','
			<< act.get_tip() << ','
			<< act.get_durata() << '\n';
	}
	fout.close();
}

const size_t ListaActivitati::get_size() const noexcept {
	return lista_activitati.size();
}

const std::vector<Activitate>& ListaActivitati::get_list() const {
	return lista_activitati;
}