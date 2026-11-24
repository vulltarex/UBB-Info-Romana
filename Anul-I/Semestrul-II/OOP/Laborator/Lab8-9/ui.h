#pragma once
#include "service.h"

class Console {
private:
	Service& srv;
	void ui_add();
	void ui_delete();
	void ui_update();
	void ui_search() const;
	void ui_show_all() const;
	void ui_filtrare() const;
	void ui_sortare() const;
	//operatii pe lista
	void ui_print_list_size() const;
	void ui_clear_list();
	void ui_add_to_list();
	void ui_generate_list();
	void ui_export_list() const;
	void ui_afisare_raport() const;
	void ui_undo();
public:
	Console(Service& srv) noexcept;
	void run();
};