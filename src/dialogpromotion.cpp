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



#include "dialogpromotion.h"
#include "ui_dialogpromotion.h"
#include "utils.h"
#include <QSettings>
#include <QDebug>


extern QMap<QString,QMap<QString,QChar>> Pieces;
extern QString InitWhitePieceColor;
extern QString InitWhiteSquareColor;
extern QString InitBlackSquareColor;
extern QString InitWhitePieceColor;
extern QString InitBlackPieceColor;

DialogPromotion::DialogPromotion(chess::Color color,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogPromotion)
{
    ui->setupUi(this);          
    setWindowFlag(Qt::FramelessWindowHint);
    QSettings s;
    
    QString fontname=s.value("PiecesFont").toString();
    QString family=Utils::getFontFamily(fontname);
    QFont font(family);
    font.setPointSize(60);
    QChar Queen=QChar(Pieces[fontname]["WHITEQUEEN"]);
    QChar Rook=QChar(Pieces[fontname]["WHITEROOK"]);
    QChar Bishop=QChar(Pieces[fontname]["WHITEBISHOP"]);
    QChar Knight=QChar(Pieces[fontname]["WHITEKNIGHT"]);
    QColor fontcolor;
    if ( color == chess::Color::WHITE)
        fontcolor=s.value("WhitePieceColor",InitWhitePieceColor).toString();
    else
        fontcolor=s.value("BlackPieceColor",InitBlackPieceColor).toString();
    QString co=QString("color: %1").arg(fontcolor.name());
    ui->toolButtonBishop->setStyleSheet(co);
    ui->toolButtonBishop->setFont(font);
    ui->toolButtonBishop->setText(Bishop);
    ui->toolButtonKnight->setStyleSheet(co);
    ui->toolButtonKnight->setFont(font);
    ui->toolButtonKnight->setText(Knight);
    ui->toolButtonQueen->setStyleSheet(co);
    ui->toolButtonQueen->setFont(font);
    ui->toolButtonQueen->setText(Queen);
    ui->toolButtonRook->setStyleSheet(co);
    ui->toolButtonRook->setFont(font);
    ui->toolButtonRook->setText(Rook);
    
    connect ( ui->toolButtonQueen,SIGNAL(clicked()),this,SLOT(QueenClicked()));
    connect ( ui->toolButtonRook,SIGNAL(clicked()),this,SLOT(CastleClicked()));
    connect ( ui->toolButtonBishop,SIGNAL(clicked()),this,SLOT(BishopClicked()));
    connect ( ui->toolButtonKnight,SIGNAL(clicked()),this,SLOT(KnightClicked()));
}

DialogPromotion::~DialogPromotion()
{
    delete ui;
}

QChar DialogPromotion::Piece() { return mPiece; }

void DialogPromotion::QueenClicked() { mPiece=QChar('q');close(); }
void DialogPromotion::CastleClicked(){ mPiece=QChar('r');close();}
void DialogPromotion::BishopClicked(){ mPiece=QChar('b');close();}
void DialogPromotion::KnightClicked(){ mPiece=QChar('k');close();}
