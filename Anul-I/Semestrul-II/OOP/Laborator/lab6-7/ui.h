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
public:
	Console(Service& srv) noexcept;
	void run();
};