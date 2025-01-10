#include "customsqlcolumnproxymodel.h"


void CustomSQLColumnProxyModel::setCustomColumnData(const QList<QVariant> &data) {
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

int CustomSQLColumnProxyModel::columnCount(const QModelIndex &parent) const {
    return QSqlQueryModel::columnCount(parent) + 1;
}

QVariant CustomSQLColumnProxyModel::data(const QModelIndex &index, int role) const {
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

bool CustomSQLColumnProxyModel::setData(const QModelIndex &index, const QVariant &value, int role) {
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

Qt::ItemFlags CustomSQLColumnProxyModel::flags(const QModelIndex &index) const {
    Qt::ItemFlags defaultFlags = QSqlQueryModel::flags(index);
    
    // Rendre la colonne personnalisée éditable
    if (index.column() == QSqlQueryModel::columnCount()) {
        return defaultFlags | Qt::ItemIsEditable;
    }
    
    return defaultFlags;
}
