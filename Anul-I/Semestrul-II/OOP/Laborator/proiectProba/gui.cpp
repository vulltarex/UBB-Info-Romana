#include "gui.h"

GUI::GUI(Service& srv) : srv{ srv } {
	initGUI();
	connectSignalsSlots();
	reloadFereastra(srv.srvGetAll());
}

void GUI::initGUI() {
	QVBoxLayout* mainLayout = new QVBoxLayout;
	this->setLayout(mainLayout);

	tblMasini = new QTableWidget(0, 3);
	mainLayout->addWidget(tblMasini);
}