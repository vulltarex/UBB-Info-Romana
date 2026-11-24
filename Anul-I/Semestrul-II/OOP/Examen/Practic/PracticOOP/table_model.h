#include <QAbstractTableModel>
#include <QModelIndex>
#include <qbrush.h>

#include "student.h"
#include <vector>

class TableModel : public QAbstractTableModel {
private:
    std::vector<Student> studenti;
public:
    TableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}
    int rowCount(const QModelIndex &parent) const override {
        return studenti.size();
    }

    int columnCount(const QModelIndex &parent) const override {
        return 4;
    }

    QVariant data(const QModelIndex &index, int role) const override {
        if (!index.isValid()) return QVariant();
        Student s = studenti[index.row()];
        if (role == Qt::DisplayRole) {
            switch (index.column()) {
                case 0: return QString::number(s.getNrMatricol());
                case 1: return QString::fromStdString(s.getNume());
                case 2: return QString::number(s.getVarsta());
                case 3: return QString::fromStdString(s.getFacultate());
            }
        }
        if (role == Qt::BackgroundRole) {
            if (s.getFacultate() == "mate") return QBrush(Qt::red);
            if (s.getFacultate() == "info") return QBrush(Qt::blue);
            if (s.getFacultate() == "mate-info") return QBrush(Qt::green);
            if (s.getFacultate() == "ai") return QBrush(Qt::magenta);
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
            switch (section) {
                case 0: return QString::fromStdString("Nr. Matricol");
                case 1: return QString::fromStdString("Nume");
                case 2: return QString::fromStdString("Varsta");
                case 3: return QString::fromStdString("Facultatea");
            }
        }
        return QVariant();
    }

    void setStudenti(const std::vector<Student>& studentiNoi) {
        beginResetModel();
        studenti = studentiNoi;
        endResetModel();
    }


};