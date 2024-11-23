#ifndef FORMUNIVERSMYPREFERENCES_H
#define FORMUNIVERSMYPREFERENCES_H

#include <QWidget>
#include <QSqlTableModel>
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
    Ui::FormUniversMyPreferences *ui;
    QSqlTableModel *model; 
    void ShowEcoPlus(QModelIndex index);
signals:
    void Informations( QString eco, QString opening, QString variation, QString ecoplus, QString moves);
};

#endif // FORMUNIVERSMYPREFERENCES_H
