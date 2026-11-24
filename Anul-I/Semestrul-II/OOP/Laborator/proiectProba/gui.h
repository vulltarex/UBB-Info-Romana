#pragma once
#include "service.h"
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QVBoxLayout>

class GUI : QWidget {
private:
	Service& srv;

	QTableWidget* tblMasini;

	QPushButton* btnSort;
	QPushButton* btnFilter;
	QPushButton* btnReset;

	QLineEdit* txtFilter;

	void initGUI();
	void connectSignalsSlots();
	void reloadFereastra(const std::vector<Masina>& masini);
public:
	GUI(Service& srv);
};