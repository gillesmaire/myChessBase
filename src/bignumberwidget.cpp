#include "bignumberwidget.h"
#include <QWidget>
#include <QPainter>
#include <QLocale>
#include <QFontDatabase>
#include <QString>

    BigNumberWidget::BigNumberWidget(QWidget *parent):QLabel(parent)
    {
        
    }
    
    void BigNumberWidget::display(qint64 number)
    {
        repaint();
    }
    
    
    void BigNumberWidget::Increment() {
        mNumber++;
        repaint();
    }
    
    void BigNumberWidget::Raz()
    {
        mNumber=mInitialNumber;
        repaint();
    }

    void BigNumberWidget::paintEvent(QPaintEvent *)  {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        QString family = QFontDatabase::applicationFontFamilies(0).at(0);
        QFont myFont(family);
        myFont.setBold(true);
        myFont.setPixelSize(180);
        myFont.setFamily(family);
        painter.setFont(myFont);
        QString str= QString("%1").arg(mNumber);
        str.remove(0,1);
        QFontMetrics metrix(painter.font());
        painter.drawText(QRectF(0,0,size().width(),size().height()),Qt::AlignHCenter,str);
     }
        
    
    
    
