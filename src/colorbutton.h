#ifndef COLORBUTTON_H
#define COLORBUTTON_H

#include <QPushButton>
#include <QPainter>


///
/// \brief The ColorButton class is a QPushButton with a color displayed on 
/// to show the color choosed
///
class ColorButton : public QPushButton
{
    Q_OBJECT
public:
    ColorButton(QWidget *parent);
    void setName(QString name);
    QColor getColor(){ return mColor;}
    void setColor( QColor color) {mColor=color;}
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
