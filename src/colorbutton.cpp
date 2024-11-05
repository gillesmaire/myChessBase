#include "colorbutton.h"

#include <QColorDialog>
#include <QSettings>
#include <QColorDialog>

ColorButton::ColorButton(QWidget *parent):QPushButton(parent)
{
    connect (this,&ColorButton::clicked,this,&ColorButton::ButtondefineColor);
}

void ColorButton::setName(QString name)
{
    mButtonName=name;
    QSettings s;
    mColor=QColor(s.value(name).toString());
}


void ColorButton::paintEvent(QPaintEvent *)
{   
    QPainter p(this);
    p.setBrush(mColor);
    p.drawRect(0,0,width(),height());
}

void ColorButton::ButtondefineColor()
{
    mColor=QColorDialog::getColor(mColor,this);
    repaint();
    emit ColorChanged(mButtonName,mColor);
    
}


