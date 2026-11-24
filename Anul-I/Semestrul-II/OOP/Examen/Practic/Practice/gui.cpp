#include "gui.h"

GUI::GUI(Service &srv) : srv(srv) {
    initGUI();
    //connectSignalSlots();
}

void GUI::initGUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);
    this->setWindowTitle("Gestiune masini");

    tblMasini = new QTableView;
    model = new TableModel;
    tblMasini->setModel(model);
    mainLayout->addWidget(tblMasini);

    sldFilter = new QSlider;
    sldFilter->setTickInterval(500);
    sldFilter->setOrientation(Qt::Horizontal);
    mainLayout->addWidget(sldFilter);
}
