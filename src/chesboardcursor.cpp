#include "chesboardcursor.h"
#include <QPixmap>
#include <QDebug>
#include <QFont>
#include <QPainter>
#include <QFontDatabase>
#include <QFile>


QCursor ChesBoardCursor::SetChessBoardCursor()
{
    QPixmap pm (QString(":/System/cursor.png"));
    QCursor cursor(pm);
    return cursor;
}

QCursor ChesBoardCursor::getCursor( int sizetile,QString fontname, QColor piececolor, int rank, int file, QColor squarecolor, ChessBoard *ptr)
{
  extern QMap<QString,QMap<QString,QChar>> Pieces;
  extern QMap <QString,int> fontList;
  QPixmap px(sizetile,sizetile);
  px.fill(Qt::transparent);
  QPainter p(&px);
  int i =fontList[fontname];
  QString family;
  if (QFontDatabase::applicationFontFamilies(i).size()!=0)
        family = QFontDatabase::applicationFontFamilies(i).at(0);
  QFont font(family);
  font.setPixelSize(sizetile+sizetile/10.0);
  p.setFont(font);
  
  QPen pen(piececolor);
  QBrush brush(piececolor);
  p.setPen(pen);
  p.setBrush(brush);
  QChar c=QChar(Pieces[fontname][ptr->getName(rank,file)]);
  p.drawText(0,px.height()/2,c);
  p.end();
  QCursor cursor(px);
  return cursor;
}
