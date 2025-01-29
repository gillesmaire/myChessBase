// GPL 3.0 License
// myChessBase Project
// Copyright (c) 2025 Gilles Maire <gilles@gillesmaire.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// THIS FILE IS AUTO GENERATED DO NOT CHANGE MANUALLY.
//
// Source: https://github.com/gillesmaire/myChessbase.git
//
//
// VERSION: 0.1

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

QCursor ChesBoardCursor::getCursor( int widthtile, int heighttile,QString fontname, QColor piececolor, int rank, int file, Color side, ChessBoard *ptr)
{
  extern QMap<QString,QMap<QString,QChar>> Pieces;
//extern QMap <QString,int> fontList;
  QPixmap px(widthtile,heighttile);
  px.fill(Qt::transparent);
  QPainter p(&px);
  QString family=Utils::getFontFamily(fontname);
  QFont font(family);
  font.setPixelSize((widthtile+heighttile)/10.0);
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
              int shiftw=widthtile*0.1;
              int shifth=heighttile*0.1;
              int biggerh=widthtile+shifth;
              font.setPixelSize(biggerh);
              p.setFont(font);
              p.setBrush(whiter);
              p.setPen(whiter);
              p.drawText(QRectF(-shiftw/2,-shifth/2,widthtile+shiftw*2,heighttile+shifth*2),QString(c));
            }
  else 
            {
              QColor darker;
              coeff=0.9;
              darker.setRedF(piececolor.redF()*coeff);
              darker.setBlueF(piececolor.blueF()*coeff);
              darker.setGreenF(piececolor.greenF()*coeff);
              int shiftw=widthtile*0.1;
              int shifth=heighttile*0.1;
              int biggerh=widthtile+shifth;
              font.setPixelSize(biggerh);
              p.setFont(font);
              p.setBrush(darker);
              p.setPen(darker);
              p.drawText(QRectF(-shiftw/2,-shifth/2,widthtile+shiftw*2,heighttile+shifth*2),QString(c));
            }
  
  font.setPixelSize(heighttile);
  p.setFont(font);
  QPen pen(piececolor);
  QBrush brush(piececolor);
  p.setPen(pen);
  p.setBrush(brush);
  //p.drawText(0,px.height()/2,c);
   p.drawText(QRectF(0,-0,widthtile,heighttile),c);
  QPixmap pm (QString(":/System/closehand.png"));
  p.drawPixmap(widthtile/4,0,widthtile/2.3,heighttile/2.3,pm);
  p.end();
  QCursor cursor(px);
  return cursor;
}
