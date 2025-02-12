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
#include "dialogpromotion.h"

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

void ChessBoard::askReloadConfiguration() {update();}

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

void ChessBoard::setFEN(QString fen) {mBoard.setFen(fen.toStdString());update();}

void ChessBoard::resizeEvent(QResizeEvent *event)
{
   extern QString InitWhiteSquareColor;
   extern QString InitBlackSquareColor;
   extern QString InitWhitePieceColor;
   extern QString InitBlackPieceColor;
   extern QString InitPieceFont;
   extern QString InitSideToPlayColor;
   
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
   mSideToPlayColor=s.value("SideToPlayColor",InitSideToPlayColor).toString();
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


void ChessBoard::mouseMoveEvent (QMouseEvent *)
{
// if ( ! mClickable ) return ;
 // QPainter painter(this);
 // if (!painter.isActive()) { qWarning("QPainter is not active (14)!"); return ;}
 //painter.drawRect(QRect(event->pos(),QSize(10,10)));
}   


bool  ChessBoard::isPromotion(QString move)
{
   bool isPromotion = true;
   QString charpromo = "qrbn";
   if (move.at(1)!=QChar('8') && move.at(1)!=QChar('1') )  
           { isPromotion=false ; } 
   if (move.length()>2  && ! charpromo.contains(move.at(2) )) 
                { isPromotion= false;  }
    return isPromotion;   
}

bool ChessBoard::isPromotion(QStringList possiblemoves) 
{
   bool isPromotion = true;
   QString charpromo = "qrbn";
   for ( auto move : possiblemoves)
   {
   if (move.at(1)!=QChar('8') && move.at(1)!=QChar('1') )  
           { isPromotion=false ; }
   if (move.length()>2  && ! charpromo.contains(move.at(2) )) 
                { isPromotion= false;  }                   

   }
   return isPromotion; 
}


QStringList ChessBoard::ListofPromotionMoves(QStringList possibleMoves)
{
  QStringList ret ;
  for ( auto m: possibleMoves)
  {
    m.chop(1);
    if (!ret.contains(m)) ret<<m;
  }
  return ret;
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
    QString cs=QString::fromStdString(std::string(sq));
    // AuthorizedCase = "e3 e4" we want hilight them
    mPossibleMoves =AuthorizedCase(cs);
    if(mPossibleMoves.isEmpty()) return;
    QColor piececolor=( mBoard.sideToMove()==Color::underlying::WHITE )?mWhitePieceColor:mBlackPieceColor;
    PieceType piecetype=mBoard.at<PieceType>(sq);
    
    //if ( piecetype == PieceType::PAWN && mPossibleMoves.containsDiagonal
    
    if ( piecetype == PieceType::PAWN && isPromotion(mPossibleMoves))
    {
        mPossibleMoves=ListofPromotionMoves(mPossibleMoves);
        QCursor cursor = ChesBoardCursor::getCursor(mTilewidth,mTileheight,mCurrentFont,piececolor,sq.rank(),sq.file(),mBoard.sideToMove(),this);
        setCursor(cursor);
        mSquareToBePlayed=Square(sq.rank(),sq.file()); 
        mMouseStatus=MouseStatus::PressedNotReleased;
        mTypeMove=Promotion;
    }
    else if  ( !mPossibleMoves.isEmpty() ) // we change the cursor 
    {
        QCursor cursor = ChesBoardCursor::getCursor(mTilewidth,mTileheight,mCurrentFont,piececolor,sq.rank(),sq.file(),mBoard.sideToMove(),this);
        setCursor(cursor);
        mSquareToBePlayed=Square(sq.rank(),sq.file()); 
        mMouseStatus=MouseStatus::PressedNotReleased;
        //mTypeMove=Normal;
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
        {
          if ( mBoard.at(mSquareToBePlayed) ==  Piece::WHITEKING ) {
                if  (mSquareToBePlayed == Square::underlying::SQ_E1 
                    &&   sq== Square::underlying::SQ_G1   )
                         move= Move::make<Move::CASTLING>(Square::underlying::SQ_E1,Square::underlying::SQ_H1);
                else if ( mSquareToBePlayed == Square::underlying::SQ_E1 
                    &&   sq== Square::underlying::SQ_C1 )
                         move= Move::make<Move::CASTLING>(Square::underlying::SQ_E1,Square::underlying::SQ_A1);
                else move = Move::make<Move::NORMAL>( mSquareToBePlayed,sq);
            }
           else if   ( mBoard.at(mSquareToBePlayed) ==  Piece::BLACKKING ) {
                if  (mSquareToBePlayed == Square::underlying::SQ_E8 
                    &&   sq== Square::underlying::SQ_G8   )
                         move= Move::make<Move::CASTLING>(Square::underlying::SQ_E8,Square::underlying::SQ_H8);
                else if ( mSquareToBePlayed == Square::underlying::SQ_E8 
                     &&   sq== Square::underlying::SQ_C8 )
                       move= Move::make<Move::CASTLING>(Square::underlying::SQ_E8,Square::underlying::SQ_A8);
                else move = Move::make<Move::NORMAL>( mSquareToBePlayed,sq);
             }  
           // pawn if square played is empty and col are diff... EN PASSANT
           //else if ( (mBoard.at(mSquareToBePlayed) == Piece::WHITEPAWN 
            //        || mBoard.at(mSquareToBePlayed) == Piece::BLACKPAWN ) && 
            //        mBoard.//
            else  if (  (mBoard.at(mSquareToBePlayed) == Piece::WHITEPAWN ||mBoard.at(mSquareToBePlayed) == Piece::BLACKPAWN ) 
                    && (abs (int(sq.file())-int(mSquareToBePlayed.file()))==1 ) 
                    && (abs (int(sq.rank())-int(mSquareToBePlayed.rank()))==1 )
                    && mBoard.at(sq)==Piece::NONE )
              move=Move::make<Move::ENPASSANT>(mSquareToBePlayed,sq);
                    
            else         
              move = Move::make<Move::NORMAL>( mSquareToBePlayed,sq);
        }
       else if ( mTypeMove==Promotion )
       {
          DialogPromotion askPiece(mBoard.sideToMove(),this);
          askPiece.exec();
          mPromotion=askPiece.Piece();
          PieceType t;
          if (mPromotion=='q') t=PieceType::QUEEN;
          else if (mPromotion=='r') t=PieceType::ROOK;
          else if (mPromotion=='b') t=PieceType::BISHOP;
          else if (mPromotion=='k') t=PieceType::KNIGHT;
          else t=PieceType::QUEEN;
          move = Move::make<Move::PROMOTION>( mSquareToBePlayed,sq,t);
       }
       mMoveSanList<<QString::fromStdString(uci::moveToSan(mBoard,move));
       mBoard.makeMove(move);
       emit MovesModifiedFromChessBoard(mMoveSanList);
       emit FENFromChessBoard(QString::fromStdString(mBoard.getFen()));
    
       mCurrent=mMoveSanList.count()-1;
       emit SetCursor(mCurrent);
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
   if (!painter->isActive()) { qWarning("QPainter is not active (3)!");return ;}
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
    if (!painter->isActive()) { qWarning("QPainter is not active (5)!"); return ;}
             QPen pen;
             pen.setWidth(0);
             QColor color(Median(mBlackSquareColor,mWhiteSquareColor));
             pen.setColor(color);
             QBrush brush(color);
             painter->setBrush(brush);
             painter->setPen(pen);
             painter->drawEllipse(QRect(mX+mTilewidth/3,mY+mTileheight/3,mTilewidth/3,mTileheight/3));
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
    if (mMoveSanList.isEmpty()) return;
    if (mCurrent==-1)  return;
    mCurrent--;
    mBoard=Board(constants::STARTPOS);
    for (int i=0; i<=mCurrent;i++) {
        Move m=uci::parseSan(mBoard,(mMoveSanList.at(i)).toStdString());
        mBoard.makeMove(m);
      }    
    update();
}

void ChessBoard::goNext()
{
   if (mMoveSanList.isEmpty()) return;
   if ( mCurrent==mMoveSanList.count()-1) return;
   else {
    QString move;
    if (mCurrent==-1)
          move=mMoveSanList.at(0);
      else {
          move= mMoveSanList.at(mCurrent+1);
      }
      mCurrent++;
      Move mu=uci::parseSan(mBoard, move.toStdString()) ;
      mBoard.makeMove(mu);
      update();
    }
}
     

void ChessBoard::goEnd()
{
   if (mMoveSanList.isEmpty()) return;
   if ( mCurrent==mMoveSanList.count()-1) return;

   while (mCurrent<mMoveSanList.count()-1)
    {
      QString move= mMoveSanList.at(mCurrent+1);
      Move mu=uci::parseSan(mBoard, move.toStdString()) ;
      mBoard.makeMove(mu);
      mCurrent++;
    }
    update();
}

void ChessBoard::paintEvent(QPaintEvent *)
{ 
    QSettings s;
    QPainter painter(this);
    if (!painter.isActive()) { qWarning("QPainter is not active (6)!"); return ;}

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
    
    DrawSideToPlay(&painter);
}

bool IsPromotion (const std::string& coup, std::string& caseDepart, std::string& caseArrivee) {
    size_t pos = coup.find('=');
    if (pos != std::string::npos) {
        caseArrivee = coup.substr(0, 2); // Ex: "bxa8=R" → "a8"

        // Trouver la case de départ (extraction du pion avant promotion)
        if (coup.length() >= 5 && (coup[1] == 'x')) { // Capture promotion ex: "bxa8=R"
            caseDepart = coup.substr(0, 1) + coup.substr(3, 1); // Ex: "bxa8=R" → "b7"
        } else { // Promotion simple (sans capture)
            caseDepart = coup.substr(0, 1) + "7"; // Ex: "b8=Q" → "b7"
        }
        return true;
    }
    return false;
}


void ChessBoard::DrawPiece( QPainter *painter)
{
     if (!painter->isActive()) { qWarning("QPainter is not active (8)!"); return ;}

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
   if (!painter->isActive()) { qWarning("QPainter is not active (10)!"); return ;}

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


void ChessBoard::DrawSideToPlay( QPainter *painter)
{ 
     if (!painter->isActive()) { qWarning("QPainter is not active (11)!"); return ;}

    painter->setBrush(mSideToPlayColor);
    painter->setPen(mSideToPlayColor);
    int sizetriangle=15;
    int mult=1;
    if ( mNumberedCase) mult=0;
    if ( mBoard.sideToMove()==Color::underlying::WHITE && ! mFlip)
       {
        QPoint p1(mShiftX-mMarginX*mult+mSize8CaseH-sizetriangle,mShiftY+mSize8CaseV);   
        QPoint p2(mShiftX-mMarginX*mult+mSize8CaseH,mShiftY+mSize8CaseV);   
        QPoint p3(mShiftX-mMarginX*mult+mSize8CaseH,mShiftY+mSize8CaseV-sizetriangle);   
        QPolygon triangle;
        triangle << p1 << p2 << p3;
        painter->drawPolygon(triangle);
       }
    else      
       {
        QPoint p1(mShiftX-mMarginX*mult+mSize8CaseH-sizetriangle,mShiftY);   
        QPoint p2(mShiftX-mMarginX*mult+mSize8CaseH,mShiftY);   
        QPoint p3(mShiftX-mMarginX*mult+mSize8CaseH,mShiftY+sizetriangle);   
        QPolygon triangle;
        triangle << p1 << p2 << p3;
        painter->drawPolygon(triangle);
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




   
