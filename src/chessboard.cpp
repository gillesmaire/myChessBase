#include "chessboard.h"
#include <QPainter>
#include <QResizeEvent>
#include <QSettings>


ChessBoard::ChessBoard(QWidget *parent ):QWidget(parent)
{
 
}

void ChessBoard::resizeEvent(QResizeEvent *event)
{
   QSettings s;
   mSize=(event->size().width()>event->size().height())? event->size().height():event->size().width();
   mWhiteSquareColor=s.value("WhiteSquareColor","#F6F5F4").toString();
   mBlackSquareColor=s.value("BlackSquareColor","#33653B").toString();
}

void ChessBoard::paintEvent(QPaintEvent *)
{ 
    QPainter painter(this);
    
    QSettings s;
    int tileSize = mSize/8;
    QColor w,b;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            // Déterminer la couleur de la case
            if ((row + col) % 2 == 0) {
               w=mWhiteSquareColor;
               painter.setBrush(w);
            } else {
                b=mBlackSquareColor;
                painter.setBrush(b); // Case noire
            }
            painter.setPen(b);
            
            // Dessiner le carré de la case
            int x = col * tileSize;
            int y = row * tileSize;
            painter.drawRect(x, y, tileSize, tileSize);
        }
    }
    
 
}
