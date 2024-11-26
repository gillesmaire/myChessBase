#ifndef CHECKBOXDELEGATE_H
#define CHECKBOXDELEGATE_H

#include <QStyledItemDelegate>
#include <QCheckBox>
#include <QModelIndex>
#include <QPainter>
#include <QStyleOptionButton>
#include <QAbstractItemView>
#include <QApplication>

class CheckBoxDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    CheckBoxDelegate(QObject *parent = nullptr);

    // Affichage de la case à cocher
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    // Créer l'éditeur (ici un QCheckBox) pour la cellule éditable
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &/*index*/) const override;

    // Pour mettre à jour le modèle avec la valeur de la case à cocher
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    // Pour enregistrer la valeur modifiée dans le modèle
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};


#endif // CHECKBOXDELEGATE_H
