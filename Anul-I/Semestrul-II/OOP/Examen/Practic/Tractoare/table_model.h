#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "tractor.h"
#include <QBrush>

class TableModel : public QAbstractTableModel {
private:
    std::vector<Tractor> tractoare;
    QString tipSelectat;
public:
    TableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return tractoare.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 5;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid()) return QVariant();

        int row = index.row();
        int col = index.column();
        const Tractor& t = tractoare[row];

        if (role == Qt::DisplayRole) {
            switch (col) {
                case 0: return t.getId();
                case 1: return QString::fromStdString(t.getDenumire());
                case 2: return QString::fromStdString(t.getTip());
                case 3: return t.getNumarRoti();
                case 4: {
                    int count = 0;
                    for (const auto& tr : tractoare) {
                        if (tr.getTip() == t.getTip()) count++;
                    }
                    return count;
                }
            }
        }
        if (role == Qt::BackgroundRole) {
            if (QString::fromStdString(t.getTip()) == tipSelectat) {
                return QBrush(Qt::red);
            }
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            switch (section) {
                case 0: return "ID";
                case 1: return "Denumire";
                case 2: return "Tip";
                case 3: return "Numar roti";
                case 4: return "Nr. tractoare de acest tip";
            }
        }
        return QVariant();
    }

    void setTractoare(const std::vector<Tractor>& tractoareNew) {
        beginResetModel();
        tractoare = tractoareNew;
        endResetModel();
    }

    void setTipSelectat(const QString& tip) {
        tipSelectat = tip;
        QModelIndex topLeft = createIndex(0,0);
        QModelIndex bottomRight = createIndex(rowCount() - 1, columnCount() - 1);
        emit dataChanged(topLeft, bottomRight);
    }
};