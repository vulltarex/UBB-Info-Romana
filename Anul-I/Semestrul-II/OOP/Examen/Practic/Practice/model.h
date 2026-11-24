#pragma once
#include <QAbstractTableModel>
#include <qbrush.h>

#include "masina.h"
#include <vector>

class TableModel : public QAbstractTableModel {
private:
    std::vector<Masina> masini;
public:
    TableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}
    void setMasini(const std::vector<Masina>& m) {
        beginResetModel();
        masini = m;
        endResetModel();
    }

    int rowCount(const QModelIndex &parent) const override {
        return masini.size();
    }
    int columnCount(const QModelIndex &parent) const override {
        return 4;
    }
    QVariant data(const QModelIndex &index, int role) const override {
        Masina m = masini[index.row()];
        if (role == Qt::DisplayRole) {
            if (index.column() == 0) return QString::number(m.getId());
            if (index.column() == 1) return QString::fromStdString(m.getModelMotor());
            if (index.column() == 2) return QString::number(m.getPutere());
            if (index.column() == 3) return QString::fromStdString(m.getStareECU());
        }
        if (role == Qt::BackgroundRole) {
            if (m.getStareECU() == "stage1") return QBrush(Qt::green);
            if (m.getStareECU() == "stoc") return QBrush(Qt::gray);
        }
        return QVariant();
    }
};
