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
  QSettings s;
  mCurrentFont=s.value("PiecesFont").toString();
  mBoard.fromFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
  
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
    piece["WHITEPAWN"]=QChar('O');
    piece["WHITEKNIGHT"]=QChar('M');
    piece["WHITEBISHOP"]=QChar('V');
    piece["WHITEROOK"]=QChar('T');
    piece["WHITEQUEEN"]=QChar('W');
    piece["WHITEKING"]=QChar('L');
    piece["BLACKPAWN"]=QChar('O');
    piece["BLACKKNIGHT"]=QChar('M');
    piece["BLACKBISHOP"]=QChar('V');
    piece["BLACKROOK"]=QChar('T');
    piece["BLACKQUEEN"]=QChar('W');
    piece["BLACKKING"]=QChar('L');
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
   extern QString InitPieceFont;
   
   QSettings s;
   mSizeBoard=(event->size().width()>event->size().height())? event->size().height():event->size().width();
   mWhiteSquareColor=s.value("WhiteSquareColor",InitWhiteSquareColor).toString();
   mBlackSquareColor=s.value("BlackSquareColor",InitBlackSquareColor).toString();
   mBlackPieceColor=s.value("BlackPieceColor",InitWhitePieceColor).toString();
   mWhitePieceColor=s.value("WhitePieceColor",InitBlackPieceColor).toString();
   mCurrentFont=s.value("PiecesFont",InitPieceFont).toString();
   emit LenghtAndColor( event->size().width()<event->size().height()?event->size().width():event->size().height() ,mBlackSquareColor);
}


QStringList  ChessBoard::AuthorizedCase(QString m)
{
    Movelist moves;
    movegen::legalmoves(moves, mBoard);
    QStringList moveList;
    for (const auto &move : moves) {
        auto mov=QString::fromStdString(uci::moveToUci(move));
        if ( mov.startsWith(m)) 
           moveList<<mov.replace(m,"");
    } 
    return moveList;
}


void ChessBoard::mousePressEvent(QMouseEvent *event)
{
    // cs = "e2"
    QString cs=QString::fromStdString(std::string(Square(NumberCase(event->pos().x(),event->pos().y()))));
    // AuthorizedCase = "e3 e4" we want hilight them
    mPossibleMoves =AuthorizedCase(cs);
    mShowPossibleMoves=true;
    
    QRectF pieceRect(mX, mY, mTileSize, mTileSize);
        if (pieceRect.contains(event->pos())) {qDebug()<<"ok";}
 
    
    
    update();
}



int ChessBoard::NumberCase( int x, int y)
{
    int sizeNumberedCase=mNumberedCase?mSizeBoard/16:0;
    int sizeCase=(mSizeBoard-2*sizeNumberedCase)/8;
    x-=sizeNumberedCase;
    y-=sizeNumberedCase;
    int line= y/sizeCase;
    int col= x/sizeCase;
    int square;
    if ( col > 7 || col < 0 ) square=64;
    if ( line > 7 || line < 0 ) square=64;
    if ( ! mFlip )
       square=(7-line)*8+col;
    else 
       square=63-(7-line)*8-col;;
    return( square);
}



QColor ChessBoard::Median( QColor color1 , QColor color2 )
{
    return QColor((color1.red()+color2.red())/2,
                  (color2.green()+color2.green())/2,
                  (color1.blue()+color2.blue())/2 );
}

void ChessBoard::DrawPossiblesMoves(QPainter *painter)
{
             QPen pen;
             pen.setWidth(0);
             QColor color(Median(mBlackSquareColor,mWhiteSquareColor));
             pen.setColor(color);
             QBrush brush(color);
             painter->setBrush(brush);
             painter->drawEllipse(QRect(mX+mTileSize/3,mY+mTileSize/3,mTileSize/3,mTileSize/3));
}

void ChessBoard::paintEvent(QPaintEvent *)
{ 
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing );
    QColor squarecolor;
    int sizeNumberedCase=mNumberedCase?mSizeBoard/16:0;
    int sizeCase=(mSizeBoard-2*sizeNumberedCase)/8;
    mSize8Case=sizeCase*8; // calculated once
    mTileSize = sizeCase;
    mShift =sizeNumberedCase?sizeCase/2:0;
    mMargin= sizeNumberedCase/8;
    squarecolor=mBlackSquareColor;
    char letter;
    char  num='1';
    for ( mRow = 0; mRow < 8; ++mRow) {
        
        if (squarecolor==mBlackSquareColor)
            squarecolor=mWhiteSquareColor;
        else 
            squarecolor=mBlackSquareColor;
        letter='a';
       
        for (mCol = 0; mCol < 8; ++mCol) 
        {  
         QString square=QString(letter)+QString(num);
            if (squarecolor==mBlackSquareColor)
                   squarecolor=mWhiteSquareColor;
            else 
                squarecolor=mBlackSquareColor;
            // Draw rect
            if (  !mFlip ){
                mY = (7-mRow) * mTileSize+mShift;
                mX=mCol*mTileSize+mShift;
            }
            else {    
                mY =mRow*mTileSize+mShift;
                mX=(7-mCol)*mTileSize+mShift;
            }  
            // draw the square
            painter.setPen(squarecolor);
            painter.setBrush(squarecolor);
            painter.drawRect(mX, mY, mTileSize, mTileSize);
            DrawPieces(&painter);
            if ( mPossibleMoves.contains(square) ) 
             { 
                DrawPossiblesMoves(&painter);
             }
          letter++;
        }
   num++;
    }
    DrawNumberedCase(&painter);
}

void ChessBoard::DrawPieces( QPainter *painter)
{
 extern QMap <QString,int> fontList;
            
            int i =fontList[mCurrentFont];
            QString family = QFontDatabase::applicationFontFamilies(i).at(0);
            QChar car=QChar(mChessFonts[mCurrentFont][getName(mRow,mCol)]);
            QColor color;
            if ( getName(mRow,mCol).startsWith("WHITE") )
                color=mWhitePieceColor;
            else if ( getName(mRow,mCol).startsWith("BLACK") )
                color=mBlackPieceColor; 
            QFont font (family);
            font.setPixelSize(mTileSize);
            painter->setPen(color);
            painter->setBrush(color);
            painter->setFont(font);
            if (color==mBlackPieceColor)
            {
              QColor whiter;
              whiter.setRedF(mWhitePieceColor.redF()*0.7);
              whiter.setBlueF(mWhitePieceColor.blueF()*0.7);
              whiter.setGreenF(mWhitePieceColor.greenF()*0.7);
              int shift=mTileSize/10.0;
              int bigger=mTileSize+shift;
              font.setPixelSize(bigger);
              painter->setFont(font);
              painter->setBrush(whiter);
              painter->setPen(whiter);
              painter->drawText(QRectF(mX-shift/2,mY-shift/2,mTileSize+shift*2,mTileSize+shift*2),QString(car));
              font.setPixelSize(mTileSize);
              painter->setFont(font);
              painter->setBrush(mBlackPieceColor);
              painter->setPen(mBlackPieceColor);
              painter->drawText(QRectF(mX,mY,mTileSize,mTileSize),QString(car));
            }
            else 
            {
              QColor darker;
              darker.setRedF(mWhitePieceColor.redF()*0.8);
              darker.setBlueF(mWhitePieceColor.blueF()*0.8);
              darker.setGreenF(mWhitePieceColor.greenF()*0.8);
              int shift=mTileSize/10.0;
              int bigger=mTileSize+shift;
              font.setPixelSize(bigger);
              painter->setFont(font);
              painter->setBrush(darker);
              painter->setPen(darker);
              painter->drawText(QRectF(mX-shift/2,mY-shift/2,mTileSize+shift*2,mTileSize+shift*2),QString(car));
              font.setPixelSize(mTileSize);
              painter->setFont(font);
              painter->setBrush(mWhitePieceColor);
              painter->setPen(mWhitePieceColor);
              painter->drawText(QRectF(mX,mY,mTileSize,mTileSize),QString(car));

            }
}
void ChessBoard::DrawNumberedCase( QPainter *painter)
{
 if ( mNumberedCase ){
        int pas= mTileSize;
        QFont f("Arial");
        f.setBold(true);
        f.setPointSize(mTileSize/5);
        painter->setFont(f); 
        painter->setPen(mBlackSquareColor);
        int pixels=QFontInfo(f).pixelSize();
        painter->drawLine(mShift,mShift-mMargin,mShift+mSize8Case,mShift-mMargin);
        painter->drawLine(mShift,mSize8Case+mShift+mMargin,mShift+mSize8Case,mSize8Case+mShift+mMargin);
        int i =1;
        if ( !mFlip) {
           for ( char car ='A' ; car <='H' ; car++ ) {
           painter->drawText(i*pas-2*mMargin,pixels+mMargin, QChar(car));
           painter->drawText(i*pas-2*mMargin,pixels+mMargin+mSize8Case+mTileSize/2, QChar(car));
           i++;
         }
        }
        else
          for ( char car ='H' ; car >='A' ; car-- ) {
          painter->drawText(i*pas-2*mMargin,pixels+mMargin, QChar(car));
          painter->drawText(i*pas-2*mMargin,pixels+mMargin+mSize8Case+mTileSize/2, QChar(car));
           i++;
         } 
        painter->drawLine(mShift-mMargin,mShift,mShift-mMargin,mSize8Case+mShift);
        painter->drawLine(mShift+mMargin+mSize8Case,mShift,mShift+mMargin+mSize8Case,mSize8Case+mShift);
        i =0;
        if (mFlip)
        {  
        for ( char car ='1' ; car <='8' ; car++ ) {
           painter->drawText(pixels-mMargin,i*pas+pas+mMargin, QChar(car));
           painter->drawText(pixels-mMargin+mSize8Case+mTileSize/2,i*pas+pas+mMargin, QChar(car));
           
           i++;
         }
        }
        else
           for ( char car ='8' ; car >='1' ; car-- ) {
               painter->drawText(pixels-mMargin,i*pas+pas+mMargin, QChar(car));
               painter->drawText(pixels-mMargin+mSize8Case+mTileSize/2,i*pas+pas+mMargin, QChar(car));
            i++;
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

void ChessBoard::setNumberCase(bool on)
{
    mNumberedCase=on;
    repaint();
}
