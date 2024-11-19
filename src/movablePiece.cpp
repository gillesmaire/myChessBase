#include "movablePiece.h"


movablePiece::movablePiece(QString piecename, QChar character, QWidget*parent):QWidget(parent),
                    mPieceName(piecename),mCharacter(character)
{
    
}

void movablePiece::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        this->move(mapToParent(event->pos() - mOffset));
    } 
}

void movablePiece::mousePressEvent(QMouseEvent *event)
{
    mOffset= event->pos();
};

