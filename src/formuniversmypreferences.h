#ifndef FORMUNIVERSMYPREFERENCES_H
#define FORMUNIVERSMYPREFERENCES_H

#include <QWidget>
#include <QSqlQueryModel>


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
    QSqlQueryModel *model; 
    void ShowEcoPlus(QModelIndex index);
signals:
    void Informations( QString eco, QString opening, QString variation, QString ecoplus, QString moves);
private slots:
    void LaunchNewRequest(bool );
    void LaunchRequest();
};

#endif // FORMUNIVERSMYPREFERENCES_H
