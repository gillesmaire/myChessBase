#include "chessboard.h"
#include <QPainter>
#include <QResizeEvent>
#include <QSettings>
#include <QFontDatabase>
#include <QLabel>
#include <QColor>




ChessBoard::ChessBoard(QWidget *parent ):QWidget(parent)
{
  RecordChessFonts();
  mFontList=mChessFonts.keys();  
  
  mCurrentFont="Alpha";
  mBoard.fromFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
  auto m1=chess::uci::uciToMove(mBoard,"e2e4");
  mBoard.makeMove(m1);
  auto m2=chess::uci::uciToMove(mBoard,"c7c6");
  mBoard.makeMove(m2);

}

QStringList ChessBoard::listOfTypeOfPieces()
{
    return (mFontList);
}

QString ChessBoard::getFEN()
{
    return QString::fromStdString(mBoard.getFen());
}

void ChessBoard::RecordChessFonts()
{
    QMap <QString, QChar> piece;
    piece["WHITEPAWN"]=QChar('o');
    piece["WHITEKNIGHT"]=QChar('m');
    piece["WHITEBISHOP"]=QChar('v');
    piece["WHITEROOK"]=QChar('t');
    piece["WHITEQUEEN"]=QChar('w');
    piece["WHITEKING"]=QChar('l');
    piece["BLACKPAWN"]=QChar('o');
    piece["BLACKKNIGHT"]=QChar('m');
    piece["BLACKBISHOP"]=QChar('v');
    piece["BLACKROOK"]=QChar('t');
    piece["BLACKQUEEN"]=QChar('w');
    piece["BLACKKING"]=QChar('l');
    piece["NOPIECE"]=QChar(' ');
    mChessFonts["Magnetic"]=piece;
    mFontName["Magnetic"]="MAGNFONT.TTF";
    piece.clear();
    piece["WHITEPAWN"]=QChar('o');
    piece["WHITEKNIGHT"]=QChar('m');
    piece["WHITEBISHOP"]=QChar('v');
    piece["WHITEROOK"]=QChar('t');
    piece["WHITEQUEEN"]=QChar('w');
    piece["WHITEKING"]=QChar('l');
    piece["BLACKPAWN"]=QChar('o');
    piece["BLACKKNIGHT"]=QChar('m');
    piece["BLACKBISHOP"]=QChar('v');
    piece["BLACKROOK"]=QChar('t');
    piece["BLACKQUEEN"]=QChar('w');
    piece["BLACKKING"]=QChar('l');
    piece["NOPIECE"]=QChar(' ');
    mChessFonts["Leipzig"]=piece;
    mFontName["Leipzig"]="LEIPFONT.TTF";
    piece.clear();
    piece["WHITEPAWN"]=QChar('o');
    piece["WHITEKNIGHT"]=QChar('m');
    piece["WHITEBISHOP"]=QChar('v');
    piece["WHITEROOK"]=QChar('t');
    piece["WHITEQUEEN"]=QChar('w');
    piece["WHITEKING"]=QChar('l');
    piece["BLACKPAWN"]=QChar('o');
    piece["BLACKKNIGHT"]=QChar('m');
    piece["BLACKBISHOP"]=QChar('v');
    piece["BLACKROOK"]=QChar('t');
    piece["BLACKQUEEN"]=QChar('w');
    piece["BLACKKING"]=QChar('l');
    piece["NOPIECE"]=QChar(' ');
    mChessFonts["Cases"]=piece;
    mFontName["Cases"]="CASEFONT.TTF";
    piece.clear();
    piece["WHITEPAWN"]=QChar('o');
    piece["WHITEKNIGHT"]=QChar('m');
    piece["WHITEBISHOP"]=QChar('v');
    piece["WHITEROOK"]=QChar('t');
    piece["WHITEQUEEN"]=QChar('w');
    piece["WHITEKING"]=QChar('l');
    piece["BLACKPAWN"]=QChar('o');
    piece["BLACKKNIGHT"]=QChar('m');
    piece["BLACKBISHOP"]=QChar('v');
    piece["BLACKROOK"]=QChar('t');
    piece["BLACKQUEEN"]=QChar('w');
    piece["BLACKKING"]=QChar('l');
    piece["NOPIECE"]=QChar(' ');
    mChessFonts["Maya"]=piece;
    mFontName["Maya"]="MAHAFONT.TTF";
    piece.clear();
    piece["WHITEPAWN"]=QChar('o');
    piece["WHITEKNIGHT"]=QChar('m');
    piece["WHITEBISHOP"]=QChar('v');
    piece["WHITEROOK"]=QChar('t');
    piece["WHITEQUEEN"]=QChar('w');
    piece["WHITEKING"]=QChar('l');
    piece["BLACKPAWN"]=QChar('o');
    piece["BLACKKNIGHT"]=QChar('m');
    piece["BLACKBISHOP"]=QChar('v');
    piece["BLACKROOK"]=QChar('t');
    piece["BLACKQUEEN"]=QChar('w');
    piece["BLACKKING"]=QChar('l');
    piece["NOPIECE"]=QChar(' ');
    mChessFonts["Chess-7"]=piece;
    mFontName["Chess-7"]="Chess-7.TTF";
    piece.clear();
    piece["WHITEPAWN"]=QChar('o');
    piece["WHITEKNIGHT"]=QChar('m');
    piece["WHITEBISHOP"]=QChar('v');
    piece["WHITEROOK"]=QChar('t');
    piece["WHITEQUEEN"]=QChar('w');
    piece["WHITEKING"]=QChar('l');
    piece["BLACKPAWN"]=QChar('o');
    piece["BLACKKNIGHT"]=QChar('m');
    piece["BLACKBISHOP"]=QChar('v');
    piece["BLACKROOK"]=QChar('t');
    piece["BLACKQUEEN"]=QChar('w');
    piece["BLACKKING"]=QChar('l');
    piece["NOPIECE"]=QChar(' ');
    mChessFonts["Marroquin"]=piece;
    mFontName["Marroquin"]="MARFONT.TTF";
    piece.clear();
    piece["WHITEPAWN"]=QChar('o');
    piece["WHITEKNIGHT"]=QChar('j');
    piece["WHITEBISHOP"]=QChar('n');
    piece["WHITEROOK"]=QChar('t');
    piece["WHITEQUEEN"]=QChar('w');
    piece["WHITEKING"]=QChar('l');
    piece["BLACKPAWN"]=QChar('o');
    piece["BLACKKNIGHT"]=QChar('j');
    piece["BLACKBISHOP"]=QChar('n');
    piece["BLACKROOK"]=QChar('t');
    piece["BLACKQUEEN"]=QChar('w');
    piece["BLACKKING"]=QChar('l');
    piece["NOPIECE"]=QChar(' ');
    mChessFonts["Alpha"]=piece;
    mFontName["Alpha"]="Alpha.ttf";
    piece.clear();
    piece["WHITEPAWN"]=QChar('o');
    piece["WHITEKNIGHT"]=QChar('j');
    piece["WHITEBISHOP"]=QChar('n');
    piece["WHITEROOK"]=QChar('t');
    piece["WHITEQUEEN"]=QChar('w');
    piece["WHITEKING"]=QChar('l');
    piece["BLACKPAWN"]=QChar('o');
    piece["BLACKKNIGHT"]=QChar('j');
    piece["BLACKBISHOP"]=QChar('n');
    piece["BLACKROOK"]=QChar('t');
    piece["BLACKQUEEN"]=QChar('w');
    piece["BLACKKING"]=QChar('l');
    piece["NOPIECE"]=QChar(' ');
    mChessFonts["Cheq"]=piece;
    mFontName["Cheq"]="CHEQ_TT.TTF";
    piece.clear();
    piece["WHITEPAWN"]=QChar('P');
    piece["WHITEKNIGHT"]=QChar('N');
    piece["WHITEBISHOP"]=QChar('B');
    piece["WHITEROOK"]=QChar('R');
    piece["WHITEQUEEN"]=QChar('Q');
    piece["WHITEKING"]=QChar('K');
    piece["BLACKPAWN"]=QChar('O');
    piece["BLACKKNIGHT"]=QChar('M');
    piece["BLACKBISHOP"]=QChar('V');
    piece["BLACKROOK"]=QChar('T');
    piece["BLACKQUEEN"]=QChar('W');
    piece["BLACKKING"]=QChar('K');
    piece["NOPIECE"]=QChar(' ');
    mChessFonts["OpenChessFont"]=piece;
    mFontName["OpenChessFont"]="OpenChessFont.ttf";
  
    
  

}

void ChessBoard::resizeEvent(QResizeEvent *event)
{
   extern QString InitWhiteSquareColor;
   extern QString InitBlackSquareColor;
   extern QString InitWhitePieceColor;
   extern QString InitBlackPieceColor;
   
   QSettings s;
   mSize=(event->size().width()>event->size().height())? event->size().height():event->size().width();
   mWhiteSquareColor=s.value("WhiteSquareColor",InitWhiteSquareColor).toString();
   mBlackSquareColor=s.value("BlackSquareColor",InitBlackSquareColor).toString();
   mBlackPieceColor=s.value("BlackPieceColor",InitWhitePieceColor).toString();
   mWhitePieceColor=s.value("WhitePieceColor",InitBlackPieceColor).toString();
}

void ChessBoard::paintEvent(QPaintEvent *)
{ 
    QPainter painter(this);
    int tileSize = mSize/8;
    QColor squarecolor;
    squarecolor=mBlackSquareColor;
    for (int row = 0; row < 8; ++row) {
              if (squarecolor==mBlackSquareColor)
                   squarecolor=mWhiteSquareColor;
              else 
                   squarecolor=mBlackSquareColor;
    
        for (int col = 0; col < 8; ++col) 
        {
              if (squarecolor==mBlackSquareColor)
                   squarecolor=mWhiteSquareColor;
              else 
                   squarecolor=mBlackSquareColor;
              painter.setBrush(squarecolor);
              painter.setPen(squarecolor);

            // Draw rect
            int x ;
            int y ;
            if (  !mFlip )
            {
                 y = (7-row) * tileSize;
                 x=col*tileSize;
            }
            else
            {    
            
                 y =row*tileSize;
                 x=(7-col)*tileSize;
            }       
            // draw the square
            painter.drawRect(x, y, tileSize, tileSize);
            
            extern QMap <QString,int> fontList;
            
            int i =fontList[mCurrentFont];
            QString family = QFontDatabase::applicationFontFamilies(i).at(0);
            QChar car=QChar(mChessFonts[mCurrentFont][getName(row,col)]);
            QColor color;
            if ( getName(row,col).startsWith("WHITE") )
                color=mWhitePieceColor;
            else if ( getName(row,col).startsWith("BLACK") )
                color=mBlackPieceColor; 
            QFont font (family);
            font.setPixelSize(tileSize);
            painter.setPen(color);
            painter.setBrush(color);
            painter.setFont(font);
            painter.drawText(QRectF(x,y,tileSize,tileSize),QString(car));
       
        }
    }
}

QString ChessBoard::getName(int row, int col)
{  
    if (mBoard.at(row*8+col)==chess::Piece::WHITEPAWN)
        return ("WHITEPAWN");
    else if (mBoard.at(row*8+col)==chess::Piece::WHITEKNIGHT)
        return ("WHITEKNIGHT");
    else if (mBoard.at(row*8+col)==chess::Piece::WHITEBISHOP)
        return ("WHITEBISHOP");
    else if (mBoard.at(row*8+col)==chess::Piece::WHITEROOK)
        return("WHITEROOK");
    else if (mBoard.at(row*8+col)==chess::Piece::WHITEQUEEN)
        return("WHITEQUEEN");
    else if (mBoard.at(row*8+col)==chess::Piece::WHITEKING)
        return("WHITEKING");
    else if (mBoard.at(row*8+col)==chess::Piece::BLACKPAWN)
        return("BLACKPAWN");
    else if (mBoard.at(row*8+col)==chess::Piece::BLACKKNIGHT)
        return("BLACKKNIGHT");
    else if (mBoard.at(row*8+col)==chess::Piece::BLACKBISHOP)
        return("BLACKBISHOP");
    else if (mBoard.at(row*8+col)==chess::Piece::BLACKROOK)    
        return("BLACKROOK");
    else if (mBoard.at(row*8+col)==chess::Piece::BLACKQUEEN)
        return("BLACKQUEEN");
    else if (mBoard.at(row*8+col)==chess::Piece::BLACKKING)
        return("BLACKKING");
    else return("NOPIECE");
}

void ChessBoard::setCurrentFont(QString font)
{
     mCurrentFont=font;
     repaint();
}
