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
#include "utils.h"
#include <QString>
#include <QSettings>
#include <QFileInfo>
//#include <QSqlDatabase>
//##include <QSqlQuery>
#include <QMessageBox>
//#include <QSqlError>
#include <QDir>
#include <QFontDatabase>
#include <QRegularExpression>

#include <chess.hpp>

extern QMap<QString,chess::PackedBoard> PackedBoards;

void Utils::RecordChessFonts()
{
    QMap<QString,QChar>P;
    extern QMap<QString,QMap<QString,QChar>> Pieces;
    P["WHITEPAWN"]='o';
    P["WHITEKNIGHT"]='m';
    P["WHITEBISHOP"]='v';
    P["WHITEROOK"]='t';
    P["WHITEQUEEN"]='w';
    P["WHITEKING"]='l';
    P["BLACKPAWN"]='o';
    P["BLACKKNIGHT"]='m';
    P["BLACKBISHOP"]='v';
    P["BLACKROOK"]='t';
    P["BLACKQUEEN"]='w';
    P["BLACKKING"]='l';
    P["NOPIECE"]=' ';
    Pieces["Magnetic"]=P;
    P.clear();

    P["WHITEPAWN"]='o';
    P["WHITEKNIGHT"]='m';
    P["WHITEBISHOP"]='v';
    P["WHITEROOK"]='t';
    P["WHITEQUEEN"]='w';
    P["WHITEKING"]='l';
    P["BLACKPAWN"]='o';
    P["BLACKKNIGHT"]='m';
    P["BLACKBISHOP"]='v';
    P["BLACKROOK"]='t';
    P["BLACKQUEEN"]='w';
    P["BLACKKING"]='l';
    P["NOPIECE"]=' ';
    Pieces["Leipzig"]=P;
    P.clear();
    
    P["WHITEPAWN"]='o';
    P["WHITEKNIGHT"]='m';
    P["WHITEBISHOP"]='v';
    P["WHITEROOK"]='t';
    P["WHITEQUEEN"]='w';
    P["WHITEKING"]='l';
    P["BLACKPAWN"]='o';
    P["BLACKKNIGHT"]='m';
    P["BLACKBISHOP"]='v';
    P["BLACKROOK"]='t';
    P["BLACKQUEEN"]='w';
    P["BLACKKING"]='l';
    P["NOPIECE"]=' ';
    Pieces["Cases"]=P;
    P.clear();
    
    P["WHITEPAWN"]='o';
    P["WHITEKNIGHT"]='m';
    P["WHITEBISHOP"]='v';
    P["WHITEROOK"]='t';
    P["WHITEQUEEN"]='w';
    P["WHITEKING"]='l';
    P["BLACKPAWN"]='o';
    P["BLACKKNIGHT"]='m';
    P["BLACKBISHOP"]='v';
    P["BLACKROOK"]='t';
    P["BLACKQUEEN"]='w';
    P["BLACKKING"]='l';
    P["NOPIECE"]=' ';
    Pieces["Maya"]=P;
    P.clear();
    
    P["WHITEPAWN"]='o';
    P["WHITEKNIGHT"]='m';
    P["WHITEBISHOP"]='v';
    P["WHITEROOK"]='t';
    P["WHITEQUEEN"]='w';
    P["WHITEKING"]='l';
    P["BLACKPAWN"]='o';
    P["BLACKKNIGHT"]='m';
    P["BLACKBISHOP"]='v';
    P["BLACKROOK"]='t';
    P["BLACKQUEEN"]='w';
    P["BLACKKING"]='l';
    P["NOPIECE"]=' ';
    Pieces["Chess-7"]=P;
    P.clear();

    P["WHITEPAWN"]='o';
    P["WHITEKNIGHT"]='m';
    P["WHITEBISHOP"]='v';
    P["WHITEROOK"]='t';
    P["WHITEQUEEN"]='w';
    P["WHITEKING"]='l';
    P["BLACKPAWN"]='o';
    P["BLACKKNIGHT"]='m';
    P["BLACKBISHOP"]='v';
    P["BLACKROOK"]='t';
    P["BLACKQUEEN"]='w';
    P["BLACKKING"]='l';
    P["NOPIECE"]=' ';
    Pieces["Marroquin"]=P;
    P.clear();

    P["WHITEPAWN"]='o';
    P["WHITEKNIGHT"]='j';
    P["WHITEBISHOP"]='n';
    P["WHITEROOK"]='t';
    P["WHITEQUEEN"]='w';
    P["WHITEKING"]='l';
    P["BLACKPAWN"]='o';
    P["BLACKKNIGHT"]='j';
    P["BLACKBISHOP"]='n';
    P["BLACKROOK"]='t';
    P["BLACKQUEEN"]='w';
    P["BLACKKING"]='l';
    P["NOPIECE"]=' ';
    Pieces["Alpha"]=P;
    P.clear();

    P["WHITEPAWN"]='o';
    P["WHITEKNIGHT"]='j';
    P["WHITEBISHOP"]='n';
    P["WHITEROOK"]='t';
    P["WHITEQUEEN"]='w';
    P["WHITEKING"]='l';
    P["BLACKPAWN"]='o';
    P["BLACKKNIGHT"]='j';
    P["BLACKBISHOP"]='n';
    P["BLACKROOK"]='t';
    P["BLACKQUEEN"]='w';
    P["BLACKKING"]='l';
    P["NOPIECE"]=' ';
    Pieces["Cheq"]=P;
    P.clear();
    
    P["WHITEPAWN"]='O';
    P["WHITEKNIGHT"]='M';
    P["WHITEBISHOP"]='V';
    P["WHITEROOK"]='T';
    P["WHITEQUEEN"]='W';
    P["WHITEKING"]='L';
    P["BLACKPAWN"]='O';
    P["BLACKKNIGHT"]='M';
    P["BLACKBISHOP"]='V';
    P["BLACKROOK"]='T';
    P["BLACKQUEEN"]='W';
    P["BLACKKING"]='L';
    P["NOPIECE"]=' ';
    Pieces["OpenChessFont"]=P;
}


QString Utils::PieceUTF8(QChar piece, chess::Color color) {
    QString pieceUTF8;

    if (piece=='N')
            pieceUTF8 = (color == chess::Color::underlying::WHITE) ? QString::fromUtf8("\u265E") : QString::fromUtf8("\u2658");
    else if (piece=='R')
            pieceUTF8 = (color == chess::Color::underlying::WHITE) ? QString::fromUtf8("\u265C") : QString::fromUtf8("\u2656");
    else if  (piece=='B')
            pieceUTF8 = (color == chess::Color::underlying::WHITE) ? QString::fromUtf8("\u265D") : QString::fromUtf8("\u2657");
    else if (piece == 'Q')
            pieceUTF8 = (color == chess::Color::underlying::WHITE) ? QString::fromUtf8("\u265B") : QString::fromUtf8("\u2655");
    else if ( piece =='K')  
            pieceUTF8 = (color == chess::Color::underlying::WHITE) ? QString::fromUtf8("\u265A") : QString::fromUtf8("\u2654");
    else    pieceUTF8 = piece;
    return pieceUTF8;
}


QString Utils::NumberSanMoves(QStringList list)
{
 QString result;
 QString white;
 QString black;
 int i=0;
 QString  first("");
 for (auto move: list)
    {
     i++;
    if ( i%2==1 ){
      white=QString("%1%2. %3").arg(first).arg(i).arg(move) ;
      first= " ";
      }
    else {
      black=move;
      result+=white + " " + black;
      white="";
     }
    }
  if ( ! white.isEmpty()) 
     result= result+ white;
  return (result);
}


QString Utils::NumberSanUTF8Moves(QStringList list)
{
 QString result;
 QString white;
 QString black;
 int i=0;
 QString  first("");
 for (auto move: list)
    {

    if ( i%2==1 ){
      QChar p=move.at(0);
      QString m=move.mid(1);
      QString l=PieceUTF8(QChar(p),chess::Color::underlying::WHITE);
      white=QString("%1%2. %3%4").arg(first).arg(i).arg(l).arg(move) ;
      first= " ";
      i++;
      }
    else {
      black=move;
      QChar p=move.at(0);
      QString m=move.mid(1);
      black=PieceUTF8(QChar(p),chess::Color::underlying::BLACK);
      result+=white + " " + black+m  ;
      white="";
     }
    }
  if ( ! white.isEmpty()) 
     result= result+ white;
  return (result);
}

QString Utils::deduceMove(chess::Board &board, QString shortmove)
{
    chess::Movelist moves;
    chess::movegen::legalmoves(moves, board);
    for (const auto &move : moves) {
        std::string m = chess::uci::moveToUci(move);
        std::string m2 = chess::uci::moveToSan(board, move);
        if (QString::fromStdString(m2) == shortmove) {
            board.makeMove(move);
            return QString::fromStdString(m);
        }
    }
    return QString("error");
}

bool Utils::MimeOK(QString text)
{
    if (text.contains("1. e4") || text.contains("1. d4") || text.contains("1. Nf3") || text.contains("1. c4") ||
        text.contains("1. a4") || text.contains("1. a3") || text.contains("1. b3")  || text.contains("1. b4") ||
        text.contains("1. c3") || text.contains("1. d3") || text.contains("1. e3")  || text.contains("1. f4") ||
        text.contains("1. f3") || text.contains("1. g4") || text.contains("1. g3")  || text.contains("1. h4") ||
        text.contains("1. h3") || text.contains("1. Nh3") || text.contains("1. Na3")  || text.contains("1. Nc3"))
        return true;
    return(false);
}

bool Utils::MimeNoBlankOK(QString text)
{
     if (text.contains("1.e4") || text.contains("1.d4") || text.contains("1.Nf3") || text.contains("1.c4") ||
        text.contains("1.a4") || text.contains("1.a3") || text.contains("1.b3")  || text.contains("1.b4") ||
        text.contains("1.c3") || text.contains("1.d3") || text.contains("1.e3")  || text.contains("1.f4") ||
        text.contains("1.f3") || text.contains("1.g4") || text.contains("1.g3")  || text.contains("1.h4") ||
        text.contains("1.h3") || text.contains("1.Nh3") || text.contains("1.Na3")  || text.contains("1.Nc3"))
        return true;
    return(false);
}


QString Utils::view2QString(std::string_view vue)
{
    return QString::fromUtf8(vue.data(), static_cast<int>(vue.size()));
}
std::string_view Utils::QString2View(const QString& qstr) {
    return std::string_view(reinterpret_cast<const char*>(qstr.utf16()), qstr.length() * 2);
   }

std::string Utils::toHexString(const std::array<uint8_t, 24> &data) {
    std::ostringstream oss;
    oss << "x'";  // Préfixe pour indiquer un BLOB en hexadécimal dans SQLite
    for (auto byte : data) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    oss << "'";
   return oss.str();
}


QString Utils::getFontFamily(QString fontname)
{
  extern QMap <QString,int> fontList;
  int i =fontList[fontname];
  if (QFontDatabase::applicationFontFamilies(i).size()!=0)
        return QFontDatabase::applicationFontFamilies(i).at(0);
 return QString();
}


QString Utils::convertMumDotPiece2NumDotBlankPiece(QString pgnname)
{   
    
    if ( MimeNoBlankOK(pgnname) ) {
        QRegularExpression re("(\\d+\\.)(\\S)");   
        pgnname.replace(re, "\\1 \\2");
    }
    return pgnname;
}


