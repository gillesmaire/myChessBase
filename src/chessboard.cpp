#include "chessboard.h"
#include <QPainter>
#include <QResizeEvent>
#include <QSettings>
#include <QFontDatabase>
#include <QLabel>
#include <QColor>
#include <chesboardcursor.h>
#include <QCoreApplication>
#include <QApplication>


ChessBoard::ChessBoard(QWidget *parent ):QWidget(parent)
{
  extern QMap<QString,QMap<QString,QChar>> Pieces;           
  RecordChessFonts();
  //mFontList=mChessFonts.keys();  
  mFontList=Pieces.keys();
  QSettings s;
  mCurrentFont=s.value("PiecesFont").toString();
  mBoard.fromFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
  QCursor cbcursor = ChesBoardCursor::SetChessBoardCursor();
  setCursor(cbcursor); 
  Move m=uci::uciToMove(mBoard,"e2e4");
  mBoard.makeMove(m);
   m=uci::uciToMove(mBoard,"e7e6");
  mBoard.makeMove(m);
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
   mBlackPieceColor=s.value("BlackPieceColor",InitBlackPieceColor).toString();
   mWhitePieceColor=s.value("WhitePieceColor",InitWhitePieceColor).toString();
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


void ChessBoard::mouseMoveEvent (QMouseEvent *event)
{
 QPainter painter(this);
 painter.drawRect(QRect(event->pos(),QSize(10,10)));
}   


void ChessBoard::mousePressEvent(QMouseEvent *event)
{
    // cs = "e2"
    QPoint p=event->pos();
    int x=p.x();
    int y=p.y();
    int nbcase=NumberCase(x,y);
    if ( nbcase < 0 || nbcase>=64) return;
    Square sq=Square(nbcase);
    QColor squarecolor=sq.is_light()?mBlackSquareColor:mWhiteSquareColor;
    QString cs=QString::fromStdString(std::string(sq));
    // AuthorizedCase = "e3 e4" we want hilight them
    mPossibleMoves =AuthorizedCase(cs);
    QColor piececolor=( mBoard.sideToMove()==Color::underlying::WHITE )?mWhitePieceColor:mBlackPieceColor;
    mShowPossibleMoves=!mPossibleMoves.isEmpty();
    if  ( mShowPossibleMoves ) // we change the cursor
    {
        QCursor cursor = ChesBoardCursor::getCursor(mTileSize,mCurrentFont,piececolor,sq.rank(),sq.file(),squarecolor,this);
        setCursor(cursor);
        mSquareToBePlayed=Square(sq.rank(),sq.file()); 
    }
    update();
}

void ChessBoard::DrawOneSquare(QPainter *painter,int x , int y, int size , QColor squarecolor)
{
    painter->setPen(squarecolor);
    painter->setBrush(squarecolor);
    painter->drawRect(x,y,size,size);
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
    if (square==64) return 64;  
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


void ChessBoard::Debug()
{       
        std::cout<<"********"<<std::endl;
        for ( int i=0; i<64; i++) {
           std::cout << std::string(mBoard.at(Square(i)))   ;
           if ( (i+1)%8 == 0 ) std::cout << std::endl;
        }
        std::cout<<"********"<<std::endl;


    
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
            DrawOneSquare(&painter,mX,mY,mTileSize,squarecolor);
            //if ()
            qDebug()<<mCol<<" "<<mRow;
             if (  mSquareToBePlayed!=Square()  && int(mSquareToBePlayed.file())  == mCol &&
                  int(mSquareToBePlayed.rank())  == mRow ) ;
                 
             else  DrawPiece(&painter);
            // mPossibleMoces is set by mousePresEvent
            if ( mPossibleMoves.contains(square) ) 
              { 
                 DrawPossiblesMoves(&painter);
              }
          letter++;
        }
   num++;
    }
    Debug();
    if (mSquareToBePlayed!=Square()) 
    {
        int rank=mSquareToBePlayed.rank();
        int file=mSquareToBePlayed.file();
        int x,y;
        DrawOneSquare(&painter,x,y,mTileSize,squarecolor);
        mSquareToBePlayed=Square();
        Debug();
    }
    
    
    DrawNumberedCase(&painter);
}

void ChessBoard::DrawPiece( QPainter *painter)
{
 extern QMap <QString,int> fontList;
 extern QMap<QString,QMap<QString,QChar>> Pieces;           
            int i =fontList[mCurrentFont];
            
            QString family;
            if (QFontDatabase::applicationFontFamilies(i).size()!=0)
                family = QFontDatabase::applicationFontFamilies(i).at(0);
                
            QChar car=QChar(Pieces[mCurrentFont][getName(mCol,mRow)]);
            
            if ( getName(mCol,mRow).startsWith("WHITE") )
                mColor=mWhitePieceColor;
            else if ( getName(mCol,mRow).startsWith("BLACK") )
                mColor=mBlackPieceColor; 
            QFont font(family);
            mFont=font;
            mFont.setPixelSize(mTileSize);
            painter->setPen(mColor);
            painter->setBrush(mColor);
            painter->setFont(mFont);
            if (mColor==mBlackPieceColor)
            {
              QColor whiter;
              whiter.setRedF(mWhitePieceColor.redF()*0.7);
              whiter.setBlueF(mWhitePieceColor.blueF()*0.7);
              whiter.setGreenF(mWhitePieceColor.greenF()*0.7);
              int shift=mTileSize/10.0;
              int bigger=mTileSize+shift;
              mFont.setPixelSize(bigger);
              painter->setFont(mFont);
              painter->setBrush(whiter);
              painter->setPen(whiter);
              painter->drawText(QRectF(mX-shift/2,mY-shift/2,mTileSize+shift*2,mTileSize+shift*2),QString(car));
              mFont.setPixelSize(mTileSize);
              painter->setFont(mFont);
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
              mFont.setPixelSize(bigger);
              painter->setFont(mFont);
              painter->setBrush(darker);
              painter->setPen(darker);
              painter->drawText(QRectF(mX-shift/2,mY-shift/2,mTileSize+shift*2,mTileSize+shift*2),QString(car));
              mFont.setPixelSize(mTileSize);
              painter->setFont(mFont);
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


QString ChessBoard::getName(int col, int row)
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
