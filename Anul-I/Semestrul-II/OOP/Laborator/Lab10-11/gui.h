#pragma once
#include "service.h"
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QTableWidget>
#include <QLabel>
#include <QMessageBox>
#include <QHeaderView>

class GUILista : public QWidget {
private:
    Service& srv;
    
    QLabel* lblSize;
    QLineEdit* txtTitlu;
    QLineEdit* txtCount;
    QLineEdit* txtExport;

    QPushButton* btnAdd;
    QPushButton* btnGenerate;
    QPushButton* btnClear;
    QPushButton* btnExport;

    void initGUI();
    void connectSignalsSlots();
    void reloadSize();

public:
    GUILista(Service& srv);
};

class GUI : public QWidget {
private:
    Service& srv;

    QListWidget* lstActivitati;
    QTableWidget* tblActivitati;

    QLineEdit* txtTitlu;
    QLineEdit* txtDescriere;
    QLineEdit* txtTip;
    QLineEdit* txtDurata;

    QPushButton* btnAdd;
    QPushButton* btnDelete;
    QPushButton* btnUpdate;
    QPushButton* btnUndo;

    QPushButton* btnSortTitlu;
    QPushButton* btnSortDescriere;
    QPushButton* btnSortTipDurata;

    QLineEdit* txtFilter;
    QPushButton* btnFilterDesc;
    QPushButton* btnFilterTip;

    QPushButton* btnReload;
    QPushButton* btnOpenLista;

    GUILista* fereastraLista;

    void initGUI();
    void connectSignalsSlots();
    void reloadList(const std::vector<Activitate>& activitati);

    QWidget* widgetButoaneDinamice;
    QVBoxLayout* layoutButoaneDinamice;

    void adaugaButoaneDinamice();

public:
    GUI(Service& srv);
};