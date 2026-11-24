#pragma once
#include "service.h"
#include "model.h"
#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QLabel>

class GUI : public QWidget {
private:
    Service& srv;
    void initGUI();
    void connectSignalSlots();

    TableModel* model;
    QTableView* tblMasini;
    QSlider* sldFilter;
    QPushButton* btnTune;

    QLabel* lblSlider;
public:
    GUI(Service& srv);
};