#pragma once
#include "service.h"
#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
#include <QLabel>
#include <QAbstractItemView>
#include <QVBoxLayout>
#include <QFormLayout>

class GUI : public QWidget {
private:
	Service& srv;

	QListWidget* lstInstrumente;

	QPushButton* btnFilterCod;
	QPushButton* btnFilterBrand;
	QPushButton* btnNefiltrat;

	QLineEdit* txtCod;
	QLineEdit* txtFilter;


	void initGUI();
	void reloadFereastra(const std::vector<Instrument>& instrumente);
	void connectSignalsSlots();
public:
	GUI(Service& srv);
};