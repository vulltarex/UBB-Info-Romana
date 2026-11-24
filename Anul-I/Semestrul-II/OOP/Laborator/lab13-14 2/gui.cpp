#include "gui.h"

CosCRUDGUI::CosCRUDGUI(Service& srv) : srv{ srv } {
	initCosCRUDGUI();
	update();
	connectSignalsSlotsLista();
	srv.srv_get_lista().addObserver(this);
}

void CosCRUDGUI::reloadFereastraLista(const std::vector<Activitate>& activitati) {
	lstActivitati->clear();
	for (const auto& a : activitati) {
		auto item = new QListWidgetItem(QString::fromStdString(a.get_titlu() + " | "
		+ a.get_descriere() + " | " + a.get_tip() + " | " + std::to_string(a.get_durata())));
		lstActivitati->addItem(item);
	}
}

CosCRUDGUI::~CosCRUDGUI() {
	srv.srv_get_lista().removeObserver(this);
}

void CosCRUDGUI::update() {
	reloadFereastraLista(srv.srv_get_activitati_lista());
	lblSize->setText(QString::number(srv.srv_get_list_size()));
}

void CosCRUDGUI::connectSignalsSlotsLista() {
	QObject::connect(btnAddLista, &QPushButton::clicked, [&]() {
		try {
			srv.srv_add_to_list(txtTitlu->text().toStdString());
		}
		catch (const RepoException& e) {
			QMessageBox::warning(this, "Eroare", QString::fromStdString(e.get_msg()));
		}
		catch (const ServiceException& e) {
			QMessageBox::warning(this, "Eroare", QString::fromStdString(e.get_msg()));
		}
		});
	QObject::connect(btnClearLista, &QPushButton::clicked, [&]() {
		srv.srv_clear_list();
		});
	QObject::connect(btnGenerateList, &QPushButton::clicked, [&]() {
		try {
			srv.srv_generate_list(numItems->value());
		}
		catch (const ServiceException& e) {
			QMessageBox::warning(this, "Eroare", QString::fromStdString(e.get_msg()));
		}
		catch (const RepoException& e) {
			QMessageBox::warning(this, "Eroare", QString::fromStdString(e.get_msg()));
		}
		});
	QObject::connect(btnExportList, &QPushButton::clicked, [&]() {
		try {
			srv.srv_export_list(txtFilename->text().toStdString());
		}
		catch (const ServiceException& e) {
			QMessageBox::warning(this, "Eroare", QString::fromStdString(e.get_msg()));
		}
		catch (const RepoException& e) {
			QMessageBox::warning(this, "Eroare", QString::fromStdString(e.get_msg()));
		}
		catch (const ListException& e) {
			QMessageBox::warning(this, "Eroare", QString::fromStdString(e.get_msg()));
		}
		});
}

void CosCRUDGUI::initCosCRUDGUI() {
	this->setWindowTitle("Lista activitati");
	QFormLayout* mainLayout = new QFormLayout;
	this->setLayout(mainLayout);

	lstActivitati = new QListWidget;
	mainLayout->addRow(lstActivitati);

	QHBoxLayout* layoutNrAct = new QHBoxLayout;

	QLabel* lblNrAct = new QLabel("Activitati in lista:");
	lblSize = new QLabel(QString::number(srv.srv_get_list_size()));
	layoutNrAct->addWidget(lblNrAct);
	layoutNrAct->addWidget(lblSize);

	mainLayout->addRow(layoutNrAct);

	txtTitlu = new QLineEdit;
	btnAddLista = new QPushButton("Adaugare in lista");
	mainLayout->addRow("Titlu activitate:", txtTitlu);
	mainLayout->addRow(btnAddLista);

	numItems = new QSpinBox;
	btnGenerateList = new QPushButton("Genereaza random");
	mainLayout->addRow("Numar activitati:", numItems);
	mainLayout->addRow(btnGenerateList);

	txtFilename = new QLineEdit;
	btnExportList = new QPushButton("Export (*.csv/*.html)");
	mainLayout->addRow("Numele fisierului:", txtFilename);
	mainLayout->addRow(btnExportList);

	btnClearLista = new QPushButton("Goleste lista");
	mainLayout->addRow(btnClearLista);
}

GUI::GUI(Service& srv) : srv{ srv } {
	initGUI();
	connectSignalsSlots();
	reloadFereastra(srv.srv_get_all());
}

void GUI::initGUI() {
	this->setWindowTitle("Management activitati");
	QHBoxLayout* mainLayout = new QHBoxLayout;
	this->setLayout(mainLayout);

	QVBoxLayout* leftLayout = new QVBoxLayout;
	lstActivitati = new QListWidget;
	lstActivitati->setSelectionMode(QAbstractItemView::SingleSelection);

	tblActivitati = new QTableView;
	modelTable = new TableModel(this);
	tblActivitati->setModel(modelTable);
	tblActivitati->setSelectionBehavior(QAbstractItemView::SelectRows);
	tblActivitati->setSelectionMode(QAbstractItemView::SingleSelection);
	tblActivitati->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	QLabel* lblSort = new QLabel("Sorteaza dupa:");
	btnSortTitlu = new QPushButton("Titlu");
	btnSortDesc = new QPushButton("Descriere");
	btnSortTipDurata = new QPushButton("Tip + Durata");

	QHBoxLayout* sortLayout = new QHBoxLayout;
	sortLayout->addWidget(lblSort);
	sortLayout->addWidget(btnSortTitlu);
	sortLayout->addWidget(btnSortDesc);
	sortLayout->addWidget(btnSortTipDurata);

	leftLayout->addWidget(lstActivitati);
	leftLayout->addWidget(tblActivitati);
	leftLayout->addLayout(sortLayout);

	mainLayout->addLayout(leftLayout);

	QVBoxLayout* rightLayout = new QVBoxLayout;
	
	QFormLayout* formLayout = new QFormLayout;
	txtTitlu = new QLineEdit;
	txtDesc = new QLineEdit;
	txtTip = new QLineEdit;
	txtDurata = new QLineEdit;
	formLayout->addRow("Titlu:", txtTitlu);
	formLayout->addRow("Descriere:", txtDesc);
	formLayout->addRow("Tip:", txtTip);
	formLayout->addRow("Durata:", txtDurata);

	rightLayout->addLayout(formLayout);

	QHBoxLayout* crudLayout = new QHBoxLayout;
	btnAdd = new QPushButton("Adauga");
	btnDel = new QPushButton("Sterge");
	btnUpdate = new QPushButton("Modifica");
	btnUndo = new QPushButton("Undo");
	
	crudLayout->addWidget(btnAdd);
	crudLayout->addWidget(btnDel);
	crudLayout->addWidget(btnUpdate);
	crudLayout->addWidget(btnUndo);
	
	rightLayout->addLayout(crudLayout);

	QFormLayout* filterLayout = new QFormLayout;
	txtFiltrare = new QLineEdit;
	filterLayout->addRow("Criteriu filtrare:", txtFiltrare);

	QHBoxLayout* btnFilterLayout = new QHBoxLayout;
	btnFiltrareDesc = new QPushButton("Filtrare Descriere");
	btnFiltrareTip = new QPushButton("Filtrare Tip");
	btnFilterLayout->addWidget(btnFiltrareDesc);
	btnFilterLayout->addWidget(btnFiltrareTip);
	filterLayout->addRow(btnFilterLayout);

	rightLayout->addLayout(filterLayout);

	btnAfisLista = new QPushButton("Afisare lista activitati");
	rightLayout->addWidget(btnAfisLista);

	btnAfisListaReadOnly = new QPushButton("Afisare lista activitati read-only");
	rightLayout->addWidget(btnAfisListaReadOnly);

	mainLayout->addLayout(rightLayout);
}

void GUI::reloadFereastra(const std::vector<Activitate>& activitati) {
	lstActivitati->clear();
	for (const auto& a : activitati) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(
			a.get_titlu() + " | " + a.get_descriere() + " | " +
			a.get_tip() + " | " + std::to_string(a.get_durata()) + " min"));
		item->setData(Qt::UserRole, QString::fromStdString(a.get_titlu()));
		item->setData(Qt::UserRole + 1, QString::fromStdString(a.get_tip()));
		lstActivitati->addItem(item);
	}

	modelTable->set_activitati(activitati);
}

void GUI::connectSignalsSlots() {
	QObject::connect(btnAdd, &QPushButton::clicked, [this]() {
		try {
			srv.srv_add(txtTitlu->text().toStdString(),
				txtDesc->text().toStdString(),
				txtTip->text().toStdString(),
				txtDurata->text().toInt());
			reloadFereastra(srv.srv_get_all());
		}
		catch (const RepoException& e) {
			QMessageBox::warning(this, "Eroare", QString::fromStdString(e.get_msg()));
		}
		catch (const ValidationException& e) {
			QMessageBox::warning(this, "Eroare", QString::fromStdString(e.get_msg()));
		}
		});

	QObject::connect(btnDel, &QPushButton::clicked, [this]() {
		try {
			srv.srv_delete(txtTitlu->text().toStdString(), txtTip->text().toStdString());
			reloadFereastra(srv.srv_get_all());
		}
		catch (const RepoException& e) {
			QMessageBox::warning(this, "Eroare", QString::fromStdString(e.get_msg()));
		}
		});
	QObject::connect(btnUpdate, &QPushButton::clicked, [this]() {
		try {
			srv.srv_update(txtTitlu->text().toStdString(),
				txtDesc->text().toStdString(),
				txtTip->text().toStdString(),
				txtDurata->text().toInt());
			reloadFereastra(srv.srv_get_all());
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
			reloadFereastra(srv.srv_get_all());
		}
		catch (const ServiceException& e) {
			QMessageBox::information(this, "Info", QString::fromStdString(e.get_msg()));
		}
		});

	QObject::connect(lstActivitati, &QListWidget::itemSelectionChanged, [this]() {
		if (lstActivitati->selectedItems().empty()) {
			txtTitlu->setText("");
			txtDesc->setText("");
			txtTip->setText("");
			txtDurata->setText("");
			return;
		}
		const QListWidgetItem* item = lstActivitati->selectedItems().at(0);
		const std::string titlu = item->data(Qt::UserRole).toString().toStdString();
		const std::string tip = item->data(Qt::UserRole + 1).toString().toStdString();
		const auto& a = srv.srv_search(titlu, tip);
		txtTitlu->setText(QString::fromStdString(a.get_titlu()));
		txtDesc->setText(QString::fromStdString(a.get_descriere()));
		txtTip->setText(QString::fromStdString(a.get_tip()));
		txtDurata->setText(QString::number(a.get_durata()));
		});

	QObject::connect(tblActivitati->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (tblActivitati->selectionModel()->selectedIndexes().isEmpty()) {
			txtTitlu->setText("");
			txtDesc->setText("");
			txtTip->setText("");
			txtDurata->setText("");
			return;
		}

		int selRow = tblActivitati->selectionModel()->selectedIndexes().at(0).row();

		auto cellTitlu = modelTable->index(selRow, 0);
		auto cellTip = modelTable->index(selRow, 2);

		const std::string titlu = modelTable->data(cellTitlu, Qt::DisplayRole).toString().toStdString();
		const std::string tip = modelTable->data(cellTip, Qt::DisplayRole).toString().toStdString();
		const auto& a = srv.srv_search(titlu, tip);
		txtTitlu->setText(QString::fromStdString(a.get_titlu()));
		txtDesc->setText(QString::fromStdString(a.get_descriere()));
		txtTip->setText(QString::fromStdString(a.get_tip()));
		txtDurata->setText(QString::number(a.get_durata()));
		});

	QObject::connect(btnFiltrareDesc, &QPushButton::clicked, [&]() {
		reloadFereastra(srv.srv_filtrare_desc(txtFiltrare->text().toStdString()));
		});
	
	QObject::connect(btnFiltrareTip, &QPushButton::clicked, [&]() {
		reloadFereastra(srv.srv_filtrare_tip(txtFiltrare->text().toStdString()));
		});

	QObject::connect(btnSortTitlu, &QPushButton::clicked, [&]() {
		reloadFereastra(srv.srv_sort_titlu());
		});
	QObject::connect(btnSortDesc, &QPushButton::clicked, [&]() {
		reloadFereastra(srv.srv_sort_desc());
		});
	QObject::connect(btnSortTipDurata, &QPushButton::clicked, [&]() {
		reloadFereastra(srv.srv_sort_tip_durata());
		});

	QObject::connect(btnAfisLista, &QPushButton::clicked, [&]() {
		auto fereastra = new CosCRUDGUI(srv);
		fereastra->setAttribute(Qt::WA_DeleteOnClose);
		fereastra->show();
		});

	QObject::connect(btnAfisListaReadOnly, &QPushButton::clicked, [&]() {
		auto fereastra = new CosReadOnlyGUI(srv);
		fereastra->setAttribute(Qt::WA_DeleteOnClose);
		fereastra->show();
		});
}

CosReadOnlyGUI::CosReadOnlyGUI(Service& srv) : srv{ srv } {
	srv.srv_get_lista().addObserver(this);
	images.push_back(QImage("img1.png"));
	images.push_back(QImage("img2.png"));
	images.push_back(QImage("img3.png"));
	images.push_back(QImage("img4.png"));
	images.push_back(QImage("img5.png"));
	images.push_back(QImage("img6.png"));
}

CosReadOnlyGUI::~CosReadOnlyGUI() {
	srv.srv_get_lista().removeObserver(this);
}

void CosReadOnlyGUI::update() {
	this->repaint();
}

void CosReadOnlyGUI::paintEvent(QPaintEvent*) {
	QPainter p{ this };
	int size = (int)srv.srv_get_list_size();

	for (int i = 0; i < size; i++) {
		int x = rand() % (this->width() - 100);
		int y = rand() % (this->height() - 100);
		int index_img = rand() % images.size();
		int scale_x = rand() % 70 + 80;
		int scale_y = rand() % 70 + 50;
		p.drawImage(x, y, images[index_img].scaled(scale_x, scale_y));
	}
}