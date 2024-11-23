#ifndef FORMTITLE_H
#define FORMTITLE_H

#include <QWidget>

namespace Ui {
class FormTitle;
}

class FormTitle : public QWidget
{
    Q_OBJECT

public:
    explicit FormTitle(QWidget *parent = nullptr);
    ~FormTitle();
    
    void setTitle(QString title);
private:
    Ui::FormTitle *ui;
};

#endif // FORMTITLE_H
