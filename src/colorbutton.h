#ifndef COLORBUTTON_H
#define COLORBUTTON_H

#include <QPushButton>
#include <QPainter>

class ColorButton : public QPushButton
{
    Q_OBJECT
public:
    ColorButton(QWidget *parent);
    void setName(QString name);
    QColor getColor(){ return mColor;}
private:
    QColor mColor;
    QString mButtonName;
    void ButtondefineColor();
protected:
    void paintEvent(QPaintEvent *e)  ;
signals:
    void ColorChanged(QString,QColor);

};


#endif // COLORBUTTON_H
