#include "gui.h"

GUI::GUI(Service& srv) : srv{ srv } {
	initGUI();
	reloadFereastra(srv.srvGetAll());
	connectSignalsSlots();
}

void GUI::initGUI() {
	QVBoxLayout* mainLayout = new QVBoxLayout;
	this->setLayout(mainLayout);
	this->setWindowTitle("Gestiune instrumente muzicale");

	lstInstrumente = new QListWidget;
	lstInstrumente->setSelectionMode(QAbstractItemView::SingleSelection);

	mainLayout->addWidget(lstInstrumente);

	QFormLayout* formLayout = new QFormLayout;
	QLabel* lblCod = new QLabel("Codul instrumentului:");
	txtCod = new QLineEdit;

	QLabel* lblCriteriu = new QLabel("Criteriu filtrare:");
	txtFilter = new QLineEdit;
	formLayout->addRow(lblCod, txtCod);
	formLayout->addRow(lblCriteriu, txtFilter);

	btnFilterCod = new QPushButton("Filtrare dupa cod");
	btnFilterBrand = new QPushButton("Filtrare dupa brand");
	btnNefiltrat = new QPushButton("Nefiltrat");

	formLayout->addRow(btnFilterBrand, btnFilterCod);
	formLayout->addRow(btnNefiltrat);

	mainLayout->addLayout(formLayout);

}

void GUI::reloadFereastra(const std::vector<Instrument>& instrumente) {
	lstInstrumente->clear();
	for (const Instrument& i : instrumente) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(i.getTip() + " | " +
			i.getBrand() + " | " + std::to_string(i.getConsumEnergetic()) + " kWh"));
		item->setData(Qt::UserRole, i.getCod());
		if (i.getTip() == "chitara") {
			item->setBackground(Qt::cyan);
		}
		else if (i.getTip() == "pian") {
			item->setBackground(Qt::gray);
		}
		else if (i.getTip() == "vioara") {
			item->setBackground(Qt::magenta);
		}
		else if (i.getTip() == "toba") {
			item->setBackground(Qt::green);
		}
		lstInstrumente->addItem(item);
	}
}

void GUI::connectSignalsSlots() {
	QObject::connect(lstInstrumente, &QListWidget::itemSelectionChanged, [this]() {
		if (lstInstrumente->selectedItems().empty()) {
			txtCod->setText("");
			return;
		}
		const QListWidgetItem* item = lstInstrumente->selectedItems().at(0);
		txtCod->setText(item->data(Qt::UserRole).toString());
		});

	QObject::connect(btnFilterBrand, &QPushButton::clicked, [this]() {
		reloadFereastra(srv.srvFilterBrand(txtFilter->text().toStdString()));
		});

	QObject::connect(btnFilterCod, &QPushButton::clicked, [this]() {
		reloadFereastra(srv.srvFilterCod(txtFilter->text().toInt()));
		});

	QObject::connect(btnNefiltrat, &QPushButton::clicked, [this]() {
		reloadFereastra(srv.srvGetAll());
		});
}