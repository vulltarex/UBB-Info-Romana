#include "gui.h"
GUI::GUI(Service& srv) : srv{ srv } {
    initGUI();
    connectSignalsSlots();
    reloadList(srv.srv_get_all());
}

void GUI::initGUI() {
    QHBoxLayout* mainLayout = new QHBoxLayout;
    this->setLayout(mainLayout);

    QVBoxLayout* leftLayout = new QVBoxLayout;
    lstActivitati = new QListWidget;
    leftLayout->addWidget(lstActivitati);

    QHBoxLayout* layoutSort = new QHBoxLayout;
    btnSortTitlu = new QPushButton("Sort Titlu");
    btnSortDescriere = new QPushButton("Sort Descriere");
    btnSortTipDurata = new QPushButton("Sort Tip+Durata");
    layoutSort->addWidget(btnSortTitlu);
    layoutSort->addWidget(btnSortDescriere);
    layoutSort->addWidget(btnSortTipDurata);
    leftLayout->addLayout(layoutSort);

    tblActivitati = new QTableWidget{ 0, 4 };
    QStringList headers;
    headers << "Titlu" << "Descriere" << "Tip" << "Durata";
    tblActivitati->setHorizontalHeaderLabels(headers);
    tblActivitati->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tblActivitati->setSelectionBehavior(QAbstractItemView::SelectRows);
    leftLayout->addWidget(tblActivitati);

    QVBoxLayout* rightLayout = new QVBoxLayout;

    QFormLayout* formLayout = new QFormLayout;
    txtTitlu = new QLineEdit;
    txtDescriere = new QLineEdit;
    txtTip = new QLineEdit;
    txtDurata = new QLineEdit;

    formLayout->addRow("Titlu:", txtTitlu);
    formLayout->addRow("Descriere:", txtDescriere);
    formLayout->addRow("Tip:", txtTip);
    formLayout->addRow("Durata:", txtDurata);
    rightLayout->addLayout(formLayout);

    QHBoxLayout* crudLayout = new QHBoxLayout;
    btnAdd = new QPushButton("Adauga");
    btnUpdate = new QPushButton("Modifica");
    btnDelete = new QPushButton("Sterge");
    btnUndo = new QPushButton("Undo");

    crudLayout->addWidget(btnAdd);
    crudLayout->addWidget(btnUpdate);
    crudLayout->addWidget(btnDelete);
    crudLayout->addWidget(btnUndo);
    rightLayout->addLayout(crudLayout);

    QFormLayout* filterLayout = new QFormLayout;
    txtFilter = new QLineEdit;
    btnFilterDesc = new QPushButton("Filtrare Descriere");
    btnFilterTip = new QPushButton("Filtrare Tip");
    filterLayout->addRow("Criteriu Filtrare:", txtFilter);
    filterLayout->addRow(btnFilterDesc, btnFilterTip);
    rightLayout->addLayout(filterLayout);

    btnReload = new QPushButton("Reincarca Toate");
    btnOpenLista = new QPushButton("Deschide Fereastra Lista/Cos");
    rightLayout->addWidget(btnReload);
    rightLayout->addWidget(btnOpenLista);

    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    widgetButoaneDinamice = new QWidget;
    layoutButoaneDinamice = new QVBoxLayout;
    widgetButoaneDinamice->setLayout(layoutButoaneDinamice);

    rightLayout->addWidget(widgetButoaneDinamice);

    adaugaButoaneDinamice();

    fereastraLista = new GUILista(srv);
}

void GUI::reloadList(const std::vector<Activitate>& activitati) {
    lstActivitati->clear();
    for (const auto& a : activitati) {
        QListWidgetItem* item = new QListWidgetItem(
            QString::fromStdString(a.get_titlu() + " | " + a.get_descriere() + " | " + a.get_tip() + " | " + std::to_string(a.get_durata()))
        );
        item->setData(Qt::UserRole, QString::fromStdString(a.get_titlu()));
        item->setData(Qt::UserRole + 1, QString::fromStdString(a.get_tip()));
        lstActivitati->addItem(item);
    }

    tblActivitati->clearContents();
    const int size = (int)activitati.size();
    tblActivitati->setRowCount(size);

    int row = 0;
    for (const auto& a : activitati) {
        QTableWidgetItem* itemTitlu = new QTableWidgetItem(QString::fromStdString(a.get_titlu()));
        itemTitlu->setData(Qt::UserRole, QString::fromStdString(a.get_titlu()));
        itemTitlu->setData(Qt::UserRole + 1, QString::fromStdString(a.get_tip()));

        tblActivitati->setItem(row, 0, itemTitlu);
        tblActivitati->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(a.get_descriere())));
        tblActivitati->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(a.get_tip())));
        tblActivitati->setItem(row, 3, new QTableWidgetItem(QString::number(a.get_durata())));
        row++;
    }
    adaugaButoaneDinamice();
}

void GUI::connectSignalsSlots() {
    QObject::connect(btnAdd, &QPushButton::clicked, [this]() {
        try {
            std::string titlu = txtTitlu->text().toStdString();
            std::string descriere = txtDescriere->text().toStdString();
            std::string tip = txtTip->text().toStdString();
            int durata = txtDurata->text().toInt();
            
            srv.srv_add(titlu, descriere, tip, durata);
            reloadList(srv.srv_get_all());
            QMessageBox::information(this, "Info", "Activitate adaugata cu succes!");
        }
        catch (const RepoException& e) {
            QMessageBox::warning(this, "Eroare Repo", QString::fromStdString(e.get_msg()));
        }
        catch (const ValidationException& e) {
            QMessageBox::warning(this, "Eroare Validare", QString::fromStdString(e.get_msg()));
        }
        });

    QObject::connect(btnDelete, &QPushButton::clicked, [this]() {
        try {
            std::string titlu = txtTitlu->text().toStdString();
            std::string tip = txtTip->text().toStdString();
            srv.srv_delete(titlu, tip);
            reloadList(srv.srv_get_all());
        }
        catch (const RepoException& e) {
            QMessageBox::warning(this, "Eroare", QString::fromStdString(e.get_msg()));
        }
        });

    QObject::connect(btnUpdate, &QPushButton::clicked, [this]() {
        try {
            std::string titlu = txtTitlu->text().toStdString();
            std::string tip = txtTip->text().toStdString();
            std::string descriere = txtDescriere->text().toStdString();
            int durata = txtDurata->text().toInt();

            srv.srv_update(titlu, descriere, tip, durata);
            reloadList(srv.srv_get_all());
        }
        catch (const RepoException& e) {
            QMessageBox::warning(this, "Eroare", QString::fromStdString(e.get_msg()));
        }
        catch (const ValidationException& e) {
            QMessageBox::warning(this, "Eroare", QString::fromStdString(e.get_msg()));
        }
        });

    QObject::connect(btnUndo, &QPushButton::clicked, [this]() {
        try {
            srv.srv_undo();
            reloadList(srv.srv_get_all());
        }
        catch (const ServiceException& e) {
            QMessageBox::warning(this, "Eroare", QString::fromStdString(e.get_msg()));
        }
        });

    QObject::connect(lstActivitati, &QListWidget::itemSelectionChanged, [this]() {
        if (lstActivitati->selectedItems().isEmpty()) {
            txtTitlu->setText("");
            txtDescriere->setText("");
            txtTip->setText("");
            txtDurata->setText("");
            return;
        }
        QListWidgetItem* selItem = lstActivitati->selectedItems().at(0);
        std::string titlu = selItem->data(Qt::UserRole).toString().toStdString();
        std::string tip = selItem->data(Qt::UserRole + 1).toString().toStdString();

        try {
            Activitate a = srv.srv_search(titlu, tip);
            txtTitlu->setText(QString::fromStdString(a.get_titlu()));
            txtDescriere->setText(QString::fromStdString(a.get_descriere()));
            txtTip->setText(QString::fromStdString(a.get_tip()));
            txtDurata->setText(QString::number(a.get_durata()));
        }
        catch (const RepoException&) {
            QMessageBox::warning(this, "Eroare", "Activitatea nu mai exista!");
        }
        });

    QObject::connect(btnSortTitlu, &QPushButton::clicked, [this]() { reloadList(srv.srv_sort_titlu()); });
    QObject::connect(btnSortDescriere, &QPushButton::clicked, [this]() { reloadList(srv.srv_sort_desc()); });
    QObject::connect(btnSortTipDurata, &QPushButton::clicked, [this]() { reloadList(srv.srv_sort_tip_durata()); });

    QObject::connect(btnFilterDesc, &QPushButton::clicked, [this]() {
        reloadList(srv.srv_filtrare_desc(txtFilter->text().toStdString()));
        });
    QObject::connect(btnFilterTip, &QPushButton::clicked, [this]() {
        reloadList(srv.srv_filtrare_tip(txtFilter->text().toStdString()));
        });

    QObject::connect(btnReload, &QPushButton::clicked, [this]() { reloadList(srv.srv_get_all()); });

    QObject::connect(btnOpenLista, &QPushButton::clicked, [this]() {
        fereastraLista->show();
        });

    QObject::connect(tblActivitati, &QTableWidget::itemSelectionChanged, [this]() {
        auto sel = tblActivitati->selectedItems();
        if (sel.isEmpty()) return;

        auto firstItem = sel.at(0);
        std::string titlu = firstItem->data(Qt::UserRole).toString().toStdString();
        std::string tip = firstItem->data(Qt::UserRole + 1).toString().toStdString();

        try {
            Activitate a = srv.srv_search(titlu, tip);
            txtTitlu->setText(QString::fromStdString(a.get_titlu()));
            txtDescriere->setText(QString::fromStdString(a.get_descriere()));
            txtTip->setText(QString::fromStdString(a.get_tip()));
            txtDurata->setText(QString::number(a.get_durata()));
        }
        catch (...) {}
        });
}

//fereastra a doua
GUILista::GUILista(Service& srv) : srv{ srv } {
    initGUI();
    connectSignalsSlots();
    reloadSize();
}

void GUILista::initGUI() {
    this->setWindowTitle("Meniu Lista / Cos Activitati");
    QVBoxLayout* layout = new QVBoxLayout;
    this->setLayout(layout);

    lblSize = new QLabel("Numar activitati in lista: 0");
    layout->addWidget(lblSize);

    QFormLayout* form = new QFormLayout;
    txtTitlu = new QLineEdit;
    btnAdd = new QPushButton("Adauga in lista (dupa titlu)");
    form->addRow("Titlu:", txtTitlu);
    form->addWidget(btnAdd);

    txtCount = new QLineEdit;
    btnGenerate = new QPushButton("Genereaza random");
    form->addRow("Numar:", txtCount);
    form->addWidget(btnGenerate);

    txtExport = new QLineEdit;
    btnExport = new QPushButton("Export (Nume fisier .csv/.html)");
    form->addRow("Nume Fisier:", txtExport);
    form->addWidget(btnExport);

    layout->addLayout(form);

    btnClear = new QPushButton("Goleste Lista");
    layout->addWidget(btnClear);
}

void GUILista::reloadSize() {
    lblSize->setText("Numar activitati in lista: " + QString::number(srv.srv_get_list_size()));
}

void GUILista::connectSignalsSlots() {
    QObject::connect(btnAdd, &QPushButton::clicked, [this]() {
        try {
            srv.srv_add_to_list(txtTitlu->text().toStdString());
            reloadSize();
        }
        catch (const ServiceException& e) {
            QMessageBox::warning(this, "Eroare", QString::fromStdString(e.get_msg()));
        }
        });

    QObject::connect(btnGenerate, &QPushButton::clicked, [this]() {
        try {
            int count = txtCount->text().toInt();
            srv.srv_generate_list(count);
            reloadSize();
        }
        catch (const ServiceException& e) {
            QMessageBox::warning(this, "Eroare", QString::fromStdString(e.get_msg()));
        }
        });

    QObject::connect(btnClear, &QPushButton::clicked, [this]() {
        srv.srv_clear_list();
        reloadSize();
        });

    QObject::connect(btnExport, &QPushButton::clicked, [this]() {
        try {
            srv.srv_export_list(txtExport->text().toStdString());
            QMessageBox::information(this, "Info", "Fisier exportat cu succes!");
        }
        catch (const ServiceException& e) {
            QMessageBox::warning(this, "Eroare Service", QString::fromStdString(e.get_msg()));
        }
        catch (const ListException& e) {
            QMessageBox::warning(this, "Eroare List", QString::fromStdString(e.get_msg()));
        }
        });
}

void GUI::adaugaButoaneDinamice() {
    QLayoutItem* item;
    while ((item = layoutButoaneDinamice->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    std::map<std::string, int> raport = srv.srv_creare_raport();

    for (const auto& pereche : raport) {
        std::string tip = pereche.first;
        int numar = pereche.second;

        QPushButton* btnTip = new QPushButton(QString::fromStdString(tip));
        layoutButoaneDinamice->addWidget(btnTip);

        QObject::connect(btnTip, &QPushButton::clicked, [this, tip, numar]() {
            QMessageBox::information(this, "Numar Activitati",
                "Exista " + QString::number(numar) + " activitati de tipul: " + QString::fromStdString(tip));
            });
    }
}