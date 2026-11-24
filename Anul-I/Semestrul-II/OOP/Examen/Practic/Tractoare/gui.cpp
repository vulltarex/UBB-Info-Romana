#include "gui.h"

GUI::GUI(Service& srv) : srv{ srv } {
    initGUI();
    //reloadFereastra(srv.srvGetAll());
    connectSignalSlots();
}

void GUI::initGUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);

    tblTractoare = new QTableView;
    model = new TableModel;
    tblTractoare->setModel(model);
    mainLayout->addWidget(tblTractoare);

    txtId = new QLineEdit;
    txtDenumire = new QLineEdit;
    txtTip = new QLineEdit;
    txtNumarRoti = new QLineEdit;
    btnAdd = new QPushButton("Adaugare");

    QFormLayout* frmLayout = new QFormLayout;

    frmLayout->addRow("ID", txtId);
    frmLayout->addRow("Denumire", txtDenumire);
    frmLayout->addRow("Tip", txtTip);
    frmLayout->addRow("Numar roti", txtNumarRoti);
    frmLayout->addRow(btnAdd);

    mainLayout->addLayout(frmLayout);

    boxTipuri = new QComboBox;
    mainLayout->addWidget(boxTipuri);
}

void GUI::connectSignalSlots() {
    QObject::connect(btnAdd, &QPushButton::clicked, [this]() {
        int id, numarRoti;
        std::string denumire, tip;
        id = txtId->text().toInt();
        denumire = txtDenumire->text().toStdString();
        tip = txtTip->text().toStdString();
        numarRoti = txtNumarRoti->text().toInt();
        try {
            srv.srvAdd(id, denumire, tip, numarRoti);
        }
        catch (const ValidationException& e) {
            QMessageBox::warning(this, "Eroare", QString::fromStdString(e.getMsg()));
        }
        catch (const RepoException& e) {
            QMessageBox::warning(this, "Eroare", QString::fromStdString(e.getMsg()));
        }
    });

    QObject::connect(boxTipuri, &QComboBox::currentIndexChanged, [this]() {
        model->setTipSelectat(boxTipuri->currentText());
    });
}

