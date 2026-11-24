#pragma once
#include "service.h"
#include "table_model.h"
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTableView>
#include <QMessageBox>
class GUI : public QWidget {
private:
    Service& srv;
    void initGUI();
    void connectSignalSlots();
    void reloadFereastra();

    QPushButton* btnPlus;
    QPushButton* btnMinus;
    QPushButton* btnDel;
    QPushButton* btnUndo;
    QPushButton* btnRedo;

    QTableView* tblStudenti;
    TableModel* model;
public:
    GUI(Service& srv) : srv(srv) {
        initGUI();
        connectSignalSlots();
        //reloadFereastra();
    }
};