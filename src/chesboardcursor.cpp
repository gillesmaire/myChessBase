#include "chesboardcursor.h"
#include <QPixmap>
#include <QDebug>
#include <QFont>
#include <QPainter>
#include <QFontDatabase>
#include <QFile>

#include "utils.h"

QCursor ChesBoardCursor::SetChessBoardCursor()
{
    QPixmap pm (QString(":/System/openhand.png"));
    QCursor cursor(pm);
    return cursor;
}

QCursor ChesBoardCursor::getCursor( int sizetile,QString fontname, QColor piececolor, int rank, int file, Color side, ChessBoard *ptr)
{
  extern QMap<QString,QMap<QString,QChar>> Pieces;
  extern QMap <QString,int> fontList;
  QPixmap px(sizetile,sizetile);
  px.fill(Qt::transparent);
  QPainter p(&px);
  QString family=Utils::getFontFamily(fontname);
  QFont font(family);
  font.setPixelSize(sizetile+sizetile/10.0);
  p.setFont(font);
  QChar c=QChar(Pieces[fontname][ptr->getName(file,rank)]);
 
  double coeff;
  
  if (side==Color::BLACK)
    {
              QColor whiter;
              coeff=0.5;
              whiter.setRedF(piececolor.redF()*coeff);
              whiter.setBlueF(piececolor.blueF()*coeff);
              whiter.setGreenF(piececolor.greenF()*coeff);
              int shift=sizetile*0.1;
              int bigger=sizetile+shift;
              font.setPixelSize(bigger);
              p.setFont(font);
              p.setBrush(whiter);
              p.setPen(whiter);
              p.drawText(QRectF(-shift/2,-shift/2,sizetile+shift*2,sizetile+shift*2),QString(c));
            }
            else 
            {
              QColor darker;
              coeff=0.9;
              darker.setRedF(piececolor.redF()*coeff);
              darker.setBlueF(piececolor.blueF()*coeff);
              darker.setGreenF(piececolor.greenF()*coeff);
              int shift=sizetile*0.1;
              int bigger=sizetile+shift;
              font.setPixelSize(bigger);
              p.setFont(font);
              p.setBrush(darker);
              p.setPen(darker);
              p.drawText(QRectF(-shift/2,-shift/2,sizetile+shift*2,sizetile+shift*2),QString(c));
            }
  
  font.setPixelSize(sizetile);
  p.setFont(font);
  QPen pen(piececolor);
  QBrush brush(piececolor);
  p.setPen(pen);
  p.setBrush(brush);
  p.drawText(0,px.height()/2,c);
  QPixmap pm (QString(":/System/closehand.png"));
  p.drawPixmap(sizetile/4,0,sizetile/2.3,sizetile/2.3,pm);
  p.end();
  
  QCursor cursor(px);
  
  
  
  
  return cursor;
}
