#ifndef DIALOGCONFIGURATION_H
#define DIALOGCONFIGURATION_H

#include <QDialog>

namespace Ui {
class DialogConfiguration;
}

class DialogConfiguration : public QDialog
{
    Q_OBJECT

public:
    explicit DialogConfiguration(QWidget *parent = nullptr);
    ~DialogConfiguration();
    
private slots:
    void ChangeColor(QString, QColor);
    void Save();
private:
    Ui::DialogConfiguration *ui;
signals:
    void sendColors( QColor colorwhitesquare, QColor colorblacksquare);
};

#endif // DIALOGCONFIGURATION_H
