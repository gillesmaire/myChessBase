#include <QPainter>
#include <QResizeEvent>
#include <QSettings>
#include <QFontDatabase>
#include <QLabel>
#include <QColor>
#include <chesboardcursor.h>
#include <QCoreApplication>
#include <QApplication>

#include "chessboard.h"

#include "utils.h"

ChessBoard::ChessBoard(QWidget *parent ):QWidget(parent)
{
  extern QMap<QString,QMap<QString,QChar>> Pieces;           
  Utils::RecordChessFonts();
  //mFontList=mChessFonts.keys();  
  mFontList=Pieces.keys();
  QSettings s;
  mCurrentFont=s.value("PiecesFont").toString();
  mBoard.fromFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
  QCursor cbcursor = ChesBoardCursor::SetChessBoardCursor();
  setCursor(cbcursor);
  mXcorrection= s.value("XShift",1).toDouble();
  
}


void ChessBoard::setCorrection(qreal x)
{
    if(mVSizeBoard/x>size().height()-80 ) return;
    mXcorrection=x;
}

bool ChessBoard::flipped() { return mFlip; }

QStringList ChessBoard::listOfTypeOfPieces()
{
    return (mFontList);
}

void ChessBoard::flipBoard(bool flip)
{
    mFlip = flip;
    update();
}

QString ChessBoard::getFEN()
{
    return QString::fromStdString(mBoard.getFen());
}


void ChessBoard::resizeEvent(QResizeEvent *event)
{
   extern QString InitWhiteSquareColor;
   extern QString InitBlackSquareColor;
   extern QString InitWhitePieceColor;
   extern QString InitBlackPieceColor;
   extern QString InitPieceFont;
   
   QSettings s;
   // mHSizeBoard= (event->size().width())/mXcorrection-120;
   // mVSizeBoard= (event->size().height())/mYcorrection-120;
   
   int size = std::min(event->size().width()*1.0, event->size().height()*mXcorrection);
   mHSizeBoard= size;
   mVSizeBoard= size;
   mWhiteSquareColor=s.value("WhiteSquareColor",InitWhiteSquareColor).toString();
   mBlackSquareColor=s.value("BlackSquareColor",InitBlackSquareColor).toString();
   mBlackPieceColor=s.value("BlackPieceColor",InitBlackPieceColor).toString();
   mWhitePieceColor=s.value("WhitePieceColor",InitWhitePieceColor).toString();
   mCurrentFont=s.value("PiecesFont",InitPieceFont).toString();
  // emit LenghtAndColor( event->size().width()<event->size().height()?event->size().width():event->size().height() ,mBlackSquareColor);
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
if ( ! mClickable ) return ;
 QPainter painter(this);
 painter.drawRect(QRect(event->pos(),QSize(10,10)));
}   


bool  ChessBoard::isPromotion(QStringList possiblemoves)
{
   bool isPromotion = true;
   QString charpromo = "qrbn";
   for (auto move: possiblemoves ) 
        { if (move.at(1)!=QChar('8') && move.at(1)!=QChar('1') )  
                { isPromotion=false ; break;} 
          if (move.length()>2  && ! charpromo.contains(move.at(2) )) 
                { isPromotion= false; break; }
        }  
    return isPromotion;   
}

void ChessBoard::mousePressEvent(QMouseEvent *event)
{
  mTypeMove=Normal;
  if ( ! mClickable ) return; 
    // cs = "e2"
    QPoint p=event->pos();
    int x=p.x();
    int y=p.y();
    int nbcase=NumberCase(x,y);
    if ( nbcase < 0 || nbcase>=64) return;
    Square sq=Square(nbcase);
   // QColor squarecolor=sq.is_light()?mBlackSquareColor:mWhiteSquareColor;
    QString cs=QString::fromStdString(std::string(sq));
    // AuthorizedCase = "e3 e4" we want hilight them
    mPossibleMoves =AuthorizedCase(cs);
   
    QColor piececolor=( mBoard.sideToMove()==Color::underlying::WHITE )?mWhitePieceColor:mBlackPieceColor;
    
    if (isPromotion(mPossibleMoves))
    {
        QStringList PromPossiblesmoves=mPossibleMoves;
        mPossibleMoves.clear();
        for ( auto i : PromPossiblesmoves)
          if (i.endsWith("q")) { i.chop(1); mPossibleMoves<<i; } 
        mTypeMove=Promotion; 
    }
    mShowPossibleMoves=!mPossibleMoves.isEmpty();
    if  ( mShowPossibleMoves ) // we change the cursor 
    {
        QCursor cursor = ChesBoardCursor::getCursor(mTilewidth,mTileheight,mCurrentFont,piececolor,sq.rank(),sq.file(),mBoard.sideToMove(),this);
        setCursor(cursor);
        mSquareToBePlayed=Square(sq.rank(),sq.file()); 
        mMouseStatus=MouseStatus::PressedNotReleased;
    }
    update();
}

void ChessBoard::mouseReleaseEvent(QMouseEvent *event)
{
    if ( ! mClickable ) return ;
    QPoint p=event->pos();
    int x=p.x();
    int y=p.y();
    int nbcase=NumberCase(x,y);
    if ( nbcase < 0 || nbcase>=64) return;
    Square sq=Square(nbcase);
    QString cs=QString::fromStdString(std::string(sq));
    
    if ( mPossibleMoves.contains(cs)) 
     {
       QString m=QString::fromStdString(std::string(mSquareToBePlayed))+cs;
       //Move move=uci::uciToMove(mBoard,m.toStdString()); 
       Move move;
       if ( mTypeMove==Normal)
          move = Move::make<Move::NORMAL>( mSquareToBePlayed,sq);
       else if ( mTypeMove==Promotion )
          move = Move::make<Move::PROMOTION>( mSquareToBePlayed,sq,PieceType::QUEEN);
       mMoveSanList<<QString::fromStdString(uci::moveToSan(mBoard,move));
       while ( mCurrent+1!=mMoveUCIList.count()) {mMoveUCIList.removeLast(); mMoveSanList.removeLast();}
       mBoard.makeMove(move);
       Debug();
       mMoveUCIList<<m;
       
       emit MovesModified(mMoveSanList);
       mCurrent=mMoveUCIList.count()-1;
       setCursor(ChesBoardCursor::SetChessBoardCursor());
       mSquareToBePlayed=Square();
       mPossibleMoves.clear();
       update();
     }
    else
     {
      setCursor(ChesBoardCursor::SetChessBoardCursor());
      mSquareToBePlayed=Square();
      mPossibleMoves.clear();
      update();
     }
}

void ChessBoard::DrawOneSquare(QPainter *painter,int x , int y, int w, int h, QColor squarecolor)
{
    painter->setPen(squarecolor);
    painter->setBrush(squarecolor);
    painter->drawRect(x,y,w,h);
}

int ChessBoard::NumberCase( int x, int y)
{
    int sizeHNumberedCase=mNumberedCase?mHSizeBoard/16:0;
    int sizeVNumberedCase=mNumberedCase?mVSizeBoard/16:0;
    int w=size().width();
    int h=w;
    int sizeHCase=(w-2*sizeHNumberedCase)/8;
    int sizeVCase=(h-2*sizeVNumberedCase)/(8*mXcorrection);
    x=x-sizeHNumberedCase;
    y=y-sizeVNumberedCase;
    int line= y/(sizeVCase);
    int col= x/sizeHCase;
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
                  (color1.green()+color2.green())/2,
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
             painter->setPen(pen);
             painter->drawEllipse(QRect(mX+mTilewidth/3,mY+mTileheight/3,mTilewidth/3,mTileheight/3));
}


void ChessBoard::Debug()
{       
        std::cout<<"********"<<std::endl;
        for ( int f=7; f>=0; f--) 
         for ( int r=0;r<=7;r++){
           Piece p = mBoard.at(Square(File(r),Rank(f)));
           std::cout << std::string(p)   ;
           if ( r==7 ) std::cout << std::endl;
        }
        std::cout<<"********"<<std::endl;
}

void ChessBoard::goStart()
{
    Board b(constants::STARTPOS);
    mBoard=b;
    mCurrent=-1;
    update();
}

void ChessBoard::goBack()
{
    if (mMoveUCIList.isEmpty()) return;
    if (mCurrent==-1)  return;
    QString move=mMoveUCIList.at(mCurrent);
    Move mu=uci::uciToMove(mBoard, move.toStdString()) ;
    if (mBoard.getFen() != constants::STARTPOS)
    {
       mBoard.unmakeMove(mu);
       if (mCurrent!=-1) mCurrent--;
       update();
    }
    Debug();
}

void ChessBoard::goNext()
{
   if (mMoveUCIList.isEmpty()) return;
   if ( mCurrent==mMoveUCIList.count()-1) return;
   else
    {
    QString move;
    if (mCurrent==-1)
          move=mMoveUCIList.at(0);
      else {
          move= mMoveUCIList.at(mCurrent+1);
          
      }
      mCurrent++;
      Move mu=uci::uciToMove(mBoard, move.toStdString()) ;
      mBoard.makeMove(mu);
      update();
    }
}
     

void ChessBoard::goEnd()
{
   if (mMoveUCIList.isEmpty()) return;
   if ( mCurrent==mMoveUCIList.count()-1) return;

   while (mCurrent<mMoveUCIList.count()-1)
    {
      QString move= mMoveUCIList.at(mCurrent+1);
      Move mu=uci::uciToMove(mBoard, move.toStdString()) ;
      mBoard.makeMove(mu);
      mCurrent++;
    }
    update();
}

void ChessBoard::paintEvent(QPaintEvent *)
{ 
    QSettings s;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QColor squarecolor;
    int sizeHNumberedCase=mNumberedCase?mHSizeBoard/16:0;
    int sizeHCase=(mHSizeBoard-2*sizeHNumberedCase)/(8);
    int sizeVNumberedCase=mNumberedCase?mVSizeBoard/16:0;
    int sizeVCase=(mHSizeBoard-2*sizeVNumberedCase)/(8*mXcorrection);

    mSize8CaseH=sizeHCase*8; // calculated once
    mSize8CaseV=sizeVCase*8; // calculated once
    mTilewidth = sizeHCase;
    mTileheight=sizeVCase;
    mShiftX=sizeHNumberedCase?sizeHCase/2:0;
    mShiftY=sizeVNumberedCase?sizeVCase/2:0;
    mMarginX= sizeHNumberedCase/8;
    mMarginY= sizeVNumberedCase/8;
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
                mY = (7-mRow) * mTileheight+mShiftY;
                mX=mCol*mTilewidth+mShiftX;
            }
            else {    
                mY =mRow*mTileheight+mShiftY;
                mX=(7-mCol)*mTilewidth+mShiftX;
            }  
            // draw the square
            DrawOneSquare(&painter,mX,mY,mTilewidth,mTileheight,squarecolor);
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
    // if (mSquareToBePlayed!=Square()) 
    // {
    //     int rank=mSquareToBePlayed.rank();
    //     int file=mSquareToBePlayed.file();
    //     int x,y;
    //     DrawOneSquare(&painter,x,y,mTileSize,squarecolor);
    //     //mSquareToBePlayed=Square();
    // }
    
    
    DrawNumberedCase(&painter);
}

void ChessBoard::DrawPiece( QPainter *painter)
{
 extern QMap<QString,QMap<QString,QChar>> Pieces; 
            int PieceSize= (mTileheight+mTilewidth)/2;
            QString family=Utils::getFontFamily(mCurrentFont);
            QChar car=QChar(Pieces[mCurrentFont][getName(mCol,mRow)]);
            
            if ( getName(mCol,mRow).startsWith("WHITE") )
                mColor=mWhitePieceColor;
            else if ( getName(mCol,mRow).startsWith("BLACK") )
                mColor=mBlackPieceColor; 
            QFont font(family);
            mFont=font;
            mFont.setPixelSize(PieceSize);
            double coeff;
            painter->setPen(mColor);
            painter->setBrush(mColor);
            painter->setFont(mFont);
            if (mColor==mBlackPieceColor)
            {
              QColor whiter;
              coeff=0.5;
              whiter.setRedF(mWhitePieceColor.redF()*coeff);
              whiter.setBlueF(mWhitePieceColor.blueF()*coeff);
              whiter.setGreenF(mWhitePieceColor.greenF()*coeff);
              int shift=PieceSize/10.0;
              int bigger=PieceSize+shift;
              mFont.setPixelSize(bigger);
              painter->setFont(mFont);
              painter->setBrush(whiter);
              painter->setPen(whiter);
              painter->drawText(QRectF(mX,mY,mTilewidth,mTileheight),Qt::AlignCenter,QString(car));
              mFont.setPixelSize(PieceSize);
              painter->setFont(mFont);
              painter->setBrush(mBlackPieceColor);
              painter->setPen(mBlackPieceColor);
              painter->drawText(QRectF(mX,mY,mTilewidth,mTileheight),Qt::AlignCenter,QString(car));
            }
            else 
            {
              QColor darker;
              coeff=0.9;
              darker.setRedF(mWhitePieceColor.redF()*coeff);
              darker.setBlueF(mWhitePieceColor.blueF()*coeff);
              darker.setGreenF(mWhitePieceColor.greenF()*coeff);
              int shift=PieceSize/10.0;
              int bigger=PieceSize+shift;
              mFont.setPixelSize(bigger);
              painter->setFont(mFont);
              painter->setBrush(darker);
              painter->setPen(darker);
              painter->drawText(QRectF(mX,mY,mTilewidth,mTileheight),Qt::AlignCenter,QString(car));
              mFont.setPixelSize(PieceSize);
              painter->setFont(mFont);
              painter->setBrush(mWhitePieceColor);
              painter->setPen(mWhitePieceColor);
              painter->drawText(QRectF(mX,mY,mTilewidth,mTileheight),Qt::AlignCenter,QString(car));
            }
}
void ChessBoard::DrawNumberedCase( QPainter *painter)
{
 if ( mNumberedCase ){
        int pas= mTilewidth;
        QFont f("Arial");
        f.setBold(true);
        f.setPointSize(mTilewidth/5);
        painter->setFont(f); 
        painter->setPen(mBlackSquareColor);
        int pixels=QFontInfo(f).pixelSize();
        painter->drawLine(mShiftX,mShiftY-mMarginY,mShiftX+mSize8CaseH,mShiftY-mMarginY);
        painter->drawLine(mShiftX,mSize8CaseV+mShiftY+mMarginY,mShiftX+mSize8CaseH,mSize8CaseV+mShiftY+mMarginY);
        int i =1;
        if ( !mFlip) {
           for ( char car ='A' ; car <='H' ; car++ ) {
           painter->drawText(i*pas-2*mMarginX,pixels+mMarginY, QChar(car));
           painter->drawText(i*pas-2*mMarginX,pixels+mMarginY+mSize8CaseV+mTilewidth*mXcorrection, QChar(car));
           i++;
         }
        }
        else
          for ( char car ='H' ; car >='A' ; car-- ) {
          painter->drawText(i*pas-2*mMarginX,pixels+mMarginY, QChar(car));
          painter->drawText(i*pas-2*mMarginX,pixels+mMarginY+mSize8CaseV+mTilewidth*mXcorrection, QChar(car));
           i++;
         } 
        painter->drawLine(mShiftX-mMarginX,mShiftY,mShiftX-mMarginX,mSize8CaseV+mShiftY);
        painter->drawLine(mShiftX+mMarginX+mSize8CaseH,mShiftY,mShiftX+mMarginX+mSize8CaseH,mSize8CaseV+mShiftY);
        i =0;
        if (mFlip)
        {  
        for ( char car ='1' ; car <='8' ; car++ ) {
           painter->drawText(pixels-mMarginX,(i/mXcorrection)*pas+pas/mXcorrection+mMarginY, QChar(car));
           painter->drawText(pixels-mMarginX+mSize8CaseH+mTilewidth/2,(i/mXcorrection)*pas+pas/mXcorrection+mMarginY, QChar(car));
           
           i++;
         }
        }
        else
           for ( char car ='8' ; car >='1' ; car-- ) {
               painter->drawText(pixels-mMarginX,(i/mXcorrection)*pas+pas/mXcorrection+mMarginY, QChar(car));
               painter->drawText(pixels-mMarginX+mSize8CaseH+mTilewidth/2,(i/mXcorrection)*pas+pas/mXcorrection+mMarginY, QChar(car));
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

void ChessBoard::setClickable(bool clickable)
{
    mClickable=clickable;
}

void ChessBoard::PlayListOfSANMove(QStringList moves)
{
    Board b(constants::STARTPOS);
    mBoard=b ;
    Move move;
    for ( auto m :  moves ) 
    {
     move=chess::uci::parseSan(mBoard,std::string_view(m.toStdString()));
     mBoard.makeMove(move);
    }
    update();
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
