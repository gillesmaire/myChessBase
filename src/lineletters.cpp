#include "lineletters.h"
#include <QPainter>
#include <QFontInfo>

LineLetters::LineLetters(QWidget *parent)
    : QWidget(parent)
{}

void LineLetters::setOrientation(bool a2h)
{
    ma2h=a2h;
    update();
    
}

void LineLetters::Reception(int lenght, QColor color)
{
     mLetterColor=color;
     mBoardLenght=lenght;
}

void LineLetters::paintEvent(QPaintEvent *)
{
   QPainter painter(this);
   painter.setPen(mLetterColor);
   int pas= mBoardLenght/8;
   QFont f("Arial");
   f.setBold(true);
   f.setPointSize(pas/5);
   painter.setFont(f);
   int pixels=QFontInfo(f).pixelSize();
   painter.drawLine(0,0,mBoardLenght,0);
   int i =0;
   
   if ( !ma2h)
   {
     for ( char car ='A' ; car <='H' ; car++ ) {
        painter.drawText(i*pas+pas/3,pixels, QChar(car));
        i++;
      }
   }
   else
     for ( char car ='H' ; car >='A' ; car-- ) {
        painter.drawText(i*pas+pas/3,30, QChar(car));
        i++;
      } 
   
  
}
