#include "gui.h"

GUI::GUI(Service& srv) : srv{ srv } {
	initGUI();
	connectSignalsSlots();
	reloadFereastra(srv.srvGetAll());
}

void GUI::initGUI() {
	QVBoxLayout* mainLayout = new QVBoxLayout;
	this->setLayout(mainLayout);

	tblAutomobile = new QTableWidget(0, 3);
	QList<QString>* headers = new QStringList;
	headers->append("Denumire");
	headers->append("Tip");
	headers->append("Necesar apa");
	tblAutomobile->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	tblAutomobile->setHorizontalHeaderLabels(*headers);
	tblAutomobile->setSelectionBehavior(QAbstractItemView::SelectRows);
	tblAutomobile->setSelectionMode(QAbstractItemView::SingleSelection);
	mainLayout->addWidget(tblAutomobile);

	btnSort = new QPushButton("Sortare dupa tip");
	btnFilter = new QPushButton("Filtrare dupa necesarul de apa");
	btnReset = new QPushButton("Reset");

	QFormLayout* layoutFilter = new QFormLayout;
	QLabel* lblFilter = new QLabel("Introduceti cantitatea maxima:");
	txtFilter = new QLineEdit;

	layoutFilter->addRow(lblFilter, txtFilter);
	mainLayout->addLayout(layoutFilter);
	mainLayout->addWidget(btnFilter);
	mainLayout->addWidget(btnSort);
	mainLayout->addWidget(btnReset);
	
	lblUdare = new QLabel("");
	mainLayout->addWidget(lblUdare);
}

void GUI::reloadFereastra(const std::vector<Automobil>& automobile) {
	tblAutomobile->clearContents();
	tblAutomobile->setRowCount(automobile.size());
	int row = 0;
	for (const auto& a : automobile) {
		QTableWidgetItem* itemDenumire = new QTableWidgetItem(QString::fromStdString(a.getDenumire()));
		QTableWidgetItem* itemTip = new QTableWidgetItem(QString::fromStdString(a.getTip()));
		QTableWidgetItem* itemNecesarApa = new QTableWidgetItem(QString::number(a.getNecesarApa()));
		itemDenumire->setData(Qt::UserRole, a.getCod());
		itemDenumire->setData(Qt::UserRole + 1, a.getNecesarApa());
		if (a.getTip() == "electrica") {
			itemDenumire->setBackground(Qt::magenta);
			itemTip->setBackground(Qt::magenta);
			itemNecesarApa->setBackground(Qt::magenta);
		}
		else if(a.getTip() == "hibrida") {
			itemDenumire->setBackground(Qt::cyan);
			itemTip->setBackground(Qt::cyan);
			itemNecesarApa->setBackground(Qt::cyan);
		}
		else if (a.getTip() == "sport") {
			itemDenumire->setBackground(Qt::red);
			itemTip->setBackground(Qt::red);
			itemNecesarApa->setBackground(Qt::red);
		}
		else if (a.getTip() == "SUV") {
			itemDenumire->setBackground(Qt::darkGray);
			itemTip->setBackground(Qt::darkGray);
			itemNecesarApa->setBackground(Qt::darkGray);
		}
		tblAutomobile->setItem(row, 0, itemDenumire);
		tblAutomobile->setItem(row, 1, itemTip);
		tblAutomobile->setItem(row, 2, itemNecesarApa);
		row++;
	}
}

void GUI::connectSignalsSlots() {
	QObject::connect(btnSort, &QPushButton::clicked, [this]() {
		reloadFereastra(srv.srvSortTip(srv.srvGetAll()));
	});

	QObject::connect(btnFilter, &QPushButton::clicked, [this]() {
		const int criteriu = txtFilter->text().toInt();
		reloadFereastra(srv.srvFilterNecesarApa(srv.srvGetAll(), criteriu));
	});

	QObject::connect(btnReset, &QPushButton::clicked, [this]() {
		reloadFereastra(srv.srvGetAll());
	});

	QObject::connect(tblAutomobile, &QTableWidget::itemSelectionChanged, [this]() {
		if (tblAutomobile->selectedItems().empty()) {
			lblUdare->setText("");
			return;
		}
		QTableWidgetItem* item = tblAutomobile->selectedItems().at(0);
		const int necesar = item->data(Qt::UserRole + 1).toInt();
		if (necesar > 300) {
			lblUdare->setText("Aceasta masina necesita udare zilnica!");
		}
		else {
			lblUdare->setText("");
		}
	});
}