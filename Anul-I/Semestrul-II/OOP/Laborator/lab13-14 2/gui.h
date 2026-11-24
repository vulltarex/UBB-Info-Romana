#pragma once
#include "service.h"
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QSpinBox>
#include <QMessageBox>
#include <QPainter>
#include <QImage>
#include <QTableView>
#include "model_tabel.h"

class CosReadOnlyGUI : public QWidget, public Observer {
private:
	Service& srv;
	std::vector<QImage> images;
public:
	CosReadOnlyGUI(Service& srv);
	~CosReadOnlyGUI();
	void update() override;
	void paintEvent(QPaintEvent* ev) override;
};

class CosCRUDGUI : public QWidget, public Observer {
private:
	Service& srv;
	QLabel* lblSize;

	QListWidget* lstActivitati;

	QPushButton* btnAddLista;
	QPushButton* btnClearLista;
	QPushButton* btnGenerateList;
	QPushButton* btnExportList;

	QLineEdit* txtTitlu;
	QLineEdit* txtFilename;
	QSpinBox* numItems;

	void initCosCRUDGUI();
	void connectSignalsSlotsLista();
	void reloadFereastraLista(const std::vector<Activitate>& activitati);
public:
	CosCRUDGUI(Service& srv);
	~CosCRUDGUI();
	void update() override;
};

class GUI : public QWidget {
private:
	Service& srv;

	QListWidget* lstActivitati;
	QTableView* tblActivitati;
	TableModel* modelTable;

	QPushButton* btnAdd;
	QPushButton* btnDel;
	QPushButton* btnUpdate;
	QPushButton* btnUndo;

	QLineEdit* txtTitlu;
	QLineEdit* txtDesc;
	QLineEdit* txtTip;
	QLineEdit* txtDurata;

	QPushButton* btnFiltrareDesc;
	QPushButton* btnFiltrareTip;
	QLineEdit* txtFiltrare;

	QPushButton* btnSortTitlu;
	QPushButton* btnSortDesc;
	QPushButton* btnSortTipDurata;

	QPushButton* btnAfisLista;
	QPushButton* btnAfisListaReadOnly;

	void initGUI();
	void connectSignalsSlots();
	void reloadFereastra(const std::vector<Activitate>& activitati);

public:
	GUI(Service& srv);
};