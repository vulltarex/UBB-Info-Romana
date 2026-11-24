#pragma once
#include "service.h"
#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QHeaderView>
#include <QFormLayout>
#include <QLabel>
#include <QAbstractItemView>

class GUI : public QWidget {
private:
	Service& srv;

	QTableWidget* tblAutomobile;

	QPushButton* btnSort;
	QPushButton* btnFilter;
	QPushButton* btnReset;

	QLineEdit* txtFilter;

	QLabel* lblUdare;

	void initGUI();
	void connectSignalsSlots();
	void reloadFereastra(const std::vector<Automobil>& automobile);
public:
	GUI(Service& srv);
};