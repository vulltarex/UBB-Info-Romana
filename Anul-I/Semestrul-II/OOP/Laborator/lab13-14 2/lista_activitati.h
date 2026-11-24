#pragma once
#include "activitate.h"
#include "observer.h"
#include <vector>

class ListException {
private:
	std::string msg;
public:
	ListException(const std::string& msg) : msg{ msg } {};
	const std::string& get_msg() const noexcept { return msg; }
};

class ListaActivitati : public Observable {
private:
	std::vector<Activitate> lista_activitati;
public:
	void clear_list() noexcept;
	void add_to_list(const Activitate& a);
	void export_html(const std::string& filename) const;
	void export_csv(const std::string& filename) const;
	const size_t get_size() const noexcept;
	const std::vector<Activitate>& get_list() const;
};