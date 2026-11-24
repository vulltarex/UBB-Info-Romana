#include "GUI.h"

void GUI::initGUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);
    this->setWindowTitle("Gestiune studenti");

    tblStudenti = new QTableView;
    model = new TableModel;
    tblStudenti->setModel(model);
    tblStudenti->setSelectionBehavior(QAbstractItemView::SelectRows);
    model->setStudenti(srv.srvGetAll());

    mainLayout->addWidget(tblStudenti);


    btnMinus = new QPushButton("Intinerire");
    btnPlus = new QPushButton("Imbatranire");

    mainLayout->addWidget(btnMinus);
    mainLayout->addWidget(btnPlus);

    btnDel = new QPushButton("Stergere");
    mainLayout->addWidget(btnDel);

    btnUndo = new QPushButton("Undo");
    btnRedo = new QPushButton("Redo");
    mainLayout->addWidget(btnUndo);
    mainLayout->addWidget(btnRedo);
}

void GUI::connectSignalSlots() {
    QObject::connect(btnPlus, &QPushButton::clicked, [this]() {
        srv.srvInc();
        model->setStudenti(srv.srvGetAll());
    });

    QObject::connect(btnMinus, &QPushButton::clicked, [this]() {
        srv.srvDec();
        model->setStudenti(srv.srvGetAll());
    });

    QObject::connect(btnDel, &QPushButton::clicked, [this]() {
        QMessageBox::warning(this, ":(", ":(");
    });

    QObject::connect(btnUndo, &QPushButton::clicked, [this]() {
        QMessageBox::warning(this, ":(", ":(");
    });

    QObject::connect(btnRedo, &QPushButton::clicked, [this]() {
        QMessageBox::warning(this, ":(", ":(");
    });
}
