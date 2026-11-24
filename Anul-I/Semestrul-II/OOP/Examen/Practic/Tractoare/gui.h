#pragma once
#include "service.h"
#include "table_model.h"
#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QTableView>
#include <QVBoxLayout>
#include <QFormLayout>

class GUI : public QWidget {
private:
    Service& srv;
    void initGUI();
    void connectSignalSlots();
    //void reloadFereastra(const std::vector<Tractor>& tractoare);

    QLineEdit* txtId;
    QLineEdit* txtDenumire;
    QLineEdit* txtTip;
    QLineEdit* txtNumarRoti;

    QPushButton* btnAdd;
    QComboBox* boxTipuri;

    QTableView* tblTractoare;
    TableModel* model;

public:
    GUI(Service& srv);
};