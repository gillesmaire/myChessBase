#include "columnnumbers.h"
#include <QPainter>


ColumnNumbers::ColumnNumbers(QWidget *parent)
    : QWidget{parent}
{}

void ColumnNumbers::setOrientation(bool a2h)
{
    ma2h=a2h;
    update();
    
}

void ColumnNumbers::Reception(int lenght, QColor color)
{
   mLetterColor=color;
   mBoardLenght=lenght;
}

void ColumnNumbers::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(mLetterColor);
    int pas= mBoardLenght/8;
    QFont f("Arial");
    f.setBold(true);
    f.setPointSize(pas/5);
    painter.setFont(f);
    int pixels=QFontInfo(f).pixelSize();
    painter.drawLine(width()-2,0,width()-2,mBoardLenght);
    int i =0;
    if ( ma2h)
     {
     for ( char car ='1' ; car <='8' ; car++ ) {
        painter.drawText(pixels,i*pas+pas/2, QChar(car));
        i++;
      }
    }
    else
     for ( char car ='8' ; car >='1' ; car-- ) {
        painter.drawText(pixels,i*pas+pas/2, QChar(car));
        i++;
      } 
    qDebug()<<ma2h<<"En fin ";
    qDebug()<<"***";
}
