#ifndef FORMUNIVERSMYPREFERENCES_H
#define FORMUNIVERSMYPREFERENCES_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QStyledItemDelegate>
#include <QCheckBox>
#include <QApplication>
#include <QPainter>

#include "customsqlcolumnproxymodel.h"

class CheckBoxDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit CheckBoxDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    // QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
    // Q_UNUSED(option);
    //    if ( index.column() == 5 )
    //      {
    //       QCheckBox *checkBox = new QCheckBox(parent);
    //       return checkBox;
    //      }
    //    return (QStyledItemDelegate::createEditor(parent, option, index));
    // }

    // void setEditorData(QWidget *editor, const QModelIndex &index) const override {
    //     if (index.column() == 5)
    //     {
    //        QCheckBox *checkbox =qobject_cast<QCheckBox *>(editor);
    //        if  ( checkbox )
    //        {
    //          bool checked = index.model()->data(index, Qt::EditRole).toBool();
    //           checkbox->setChecked(checked);
    //        }
    //     }
    //     else QStyledItemDelegate::setEditorData(editor,index);
    // }

    // void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override {
    //     if ( index.column()==5 )
    //     {
    //       QCheckBox *checkBox = qobject_cast<QCheckBox *>(editor);
    //     if (checkBox) {
    //         model->setData(index, checkBox->isChecked(), Qt::EditRole);
    //     }
    //     }
    //     else QStyledItemDelegate::setModelData(editor,model,index);
    // }

      void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
    
   
 
}

 
 
};



namespace Ui {
class FormUniversMyPreferences;
}

class FormUniversMyPreferences : public QWidget
{
    Q_OBJECT

public:
    explicit FormUniversMyPreferences(QWidget *parent = nullptr);
    ~FormUniversMyPreferences();

private:
    CustomSQLColumnProxyModel* mSqlModel;
    //QSqlQueryModel *mSqlModel;
    Ui::FormUniversMyPreferences *ui;
    void ShowEcoPlus(QModelIndex index);
    CheckBoxDelegate *mdelegate;
signals:
    void Informations( QString eco, QString opening, QString variation, QString ecoplus, QString moves);
private slots:
    void LaunchNewRequest(bool );
    void LaunchRequest();
};

#endif // FORMUNIVERSMYPREFERENCES_H
