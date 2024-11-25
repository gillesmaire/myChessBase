#ifndef CUSTOMSQLCOLUMNPROXYMODEL_H
#define CUSTOMSQLCOLUMNPROXYMODEL_H

#include <QSqlQueryModel>
#include <QList>
#include <QDebug>

class CustomSQLColumnProxyModel : public QSqlQueryModel {
    Q_OBJECT

public:
    explicit CustomSQLColumnProxyModel(QObject* parent = nullptr)
        : QSqlQueryModel(parent) {}

    void setCustomColumnData(const QList<QVariant>& data) {
        m_customColumnData = data;

        int rowCount = QSqlQueryModel::rowCount();
        if (m_customColumnData.size() != rowCount) {
            m_customColumnData.resize(rowCount);
            for (int i = 0; i < rowCount; ++i) {
                if (m_customColumnData[i].isNull())
                    m_customColumnData[i] = QVariant(); // Initialisation par défaut
            }
        }

        // Notifie les vues que les données ont changé
        emit dataChanged(index(0, columnCount() - 1), index(rowCount - 1, columnCount() - 1));
    }

    // Renvoie le nombre total de colonnes (ajout d'une colonne personnalisée)
    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return QSqlQueryModel::columnCount(parent) + 1;
    }
    // Renvoie les données d'une cellule
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid()) {
            return QVariant();
        }

        // Gestion de la colonne personnalisée
        if (index.column() == QSqlQueryModel::columnCount()) { // Colonne supplémentaire
            if (role == Qt::DisplayRole || role == Qt::EditRole) {
            
                if (index.row() < m_customColumnData.size()) {
                    return m_customColumnData[index.row()];
                }
                return QVariant(); // Valeur par défaut si hors limites
            }
        }

        // Gestion des colonnes standards
        return QSqlQueryModel::data(index, role);
    }

    // Gestion de l'édition pour la colonne personnalisée
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override {
        if (!index.isValid() || role != Qt::EditRole) {
            return false;
        }

        // Colonne personnalisée
        if (index.column() == QSqlQueryModel::columnCount()) {
            if (index.row() < m_customColumnData.size()) {
                m_customColumnData[index.row()] = value;
                emit dataChanged(index, index);
                return true;
            }
            return false;
        }

        // Colonnes standards (non modifiables ici)
        return QSqlQueryModel::setData(index, value, role);
    }

    // Indique quelles cellules sont éditables
    Qt::ItemFlags flags(const QModelIndex& index) const override {
        Qt::ItemFlags defaultFlags = QSqlQueryModel::flags(index);

        // Rendre la colonne personnalisée éditable
        if (index.column() == QSqlQueryModel::columnCount()) {
            return defaultFlags | Qt::ItemIsEditable;
        }

        return defaultFlags;
    }

private:
    QList<QVariant> m_customColumnData; // Données de la colonne personnalisée
};
#endif // CUSTOMSQLCOLUMNPROXYMODEL_H
