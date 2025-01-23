#ifndef FORMCONFIG_H
#define FORMCONFIG_H

#include <QWidget>

namespace Ui {
class FormConfig;
}

class FormConfig : public QWidget
{
    Q_OBJECT

public:
    explicit FormConfig(QWidget *parent = nullptr);
    ~FormConfig();


private slots:
    void ChangeColor(QString, QColor);
    void Save();
    void ChangePiece(QString name );
    void SaveInformations();
    
private:
    Ui::FormConfig *ui;
    QFont mCurrentFont;
signals:
    void askRefresh();
};

#endif // FORMCONFIG_H
