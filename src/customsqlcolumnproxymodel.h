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

    void setCustomColumnData(const QList<QVariant>& data);

    // Renvoie le nombre total de colonnes (ajout d'une colonne personnalisée)
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    // Renvoie les données d'une cellule
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    // Gestion de l'édition pour la colonne personnalisée
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

    // Indique quelles cellules sont éditables
    Qt::ItemFlags flags(const QModelIndex& index) const override;

private:
    QList<QVariant> m_customColumnData; // Données de la colonne personnalisée
};
#endif // CUSTOMSQLCOLUMNPROXYMODEL_H
