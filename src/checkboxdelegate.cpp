#include "checkboxdelegate.h"


CheckBoxDelegate::CheckBoxDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

void CheckBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (index.isValid()) {
        // Utiliser le style du système pour dessiner la case
        QStyleOptionButton checkboxStyleOption;
        checkboxStyleOption.rect = option.rect;
        checkboxStyleOption.state = (index.data().toBool()) ? QStyle::State_On : QStyle::State_Off;
        QApplication::style()->drawControl(QStyle::CE_CheckBox, &checkboxStyleOption, painter);
    }
}

QWidget *CheckBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const {
    QCheckBox *editor = new QCheckBox(parent);
    return editor;
}

void CheckBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    QCheckBox *checkBox = qobject_cast<QCheckBox *>(editor);
    if (checkBox) {
        checkBox->setChecked(index.data().toBool());
    }
}

void CheckBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    QCheckBox *checkBox = qobject_cast<QCheckBox *>(editor);
    
    if (checkBox) {
        model->setData(index, checkBox->isChecked());
    }
}
