#pragma once

#include <QAbstractTableModel>
#include <vector>
#include "activitate.h"

class TableModel : public QAbstractTableModel {
private:
	std::vector<Activitate> activitati;
public:
	TableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

	void set_activitati(const std::vector<Activitate>& activitati_new) {
		beginResetModel();
		activitati = activitati_new;
		endResetModel();
	}

	int rowCount(const QModelIndex& = QModelIndex()) const override {
		return (int)activitati.size();
	}

	int columnCount(const QModelIndex& = QModelIndex()) const override {
		return 4;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			Activitate a = activitati[index.row()];
			if (index.column() == 0) return QString::fromStdString(a.get_titlu());
			if (index.column() == 1) return QString::fromStdString(a.get_descriere());
			if (index.column() == 2) return QString::fromStdString(a.get_tip());
			if (index.column() == 3) return QString::number(a.get_durata());
		}
		return QVariant();
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
			if (section == 0) return "Titlu";
			if (section == 1) return "Descriere";
			if (section == 2) return "Tip";
			if (section == 3) return "Durata";
		}
		return QVariant();
	}
};