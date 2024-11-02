#ifndef BIGNUMBERWIDGET_H
#define BIGNUMBERWIDGET_H

#include <QWidget>
#include <QLabel>

class BigNumberWidget : public QLabel
{
    Q_OBJECT
public:
    explicit BigNumberWidget(QWidget *parent);
    void display(qint64 number);
    void Increment();
    void Raz();
protected:
    void paintEvent(QPaintEvent *);
private:
    qint64 mInitialNumber=1000000000000;
    qint64 mNumber=mInitialNumber;
    
};

#endif // BIGNUMBERWIDGET_H
