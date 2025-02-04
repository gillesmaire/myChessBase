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

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include "chess.hpp"
#include <QMap>
 using namespace chess;



typedef enum {PossibleMoves,LastMove,Nothing}  Raison;


class ChessBoard : public QWidget
{
     Q_OBJECT
    typedef enum { Normal, Promotion, Castle} TypeMove;
public:
    explicit ChessBoard(QWidget *widget);
    void setWhiteSquareColor( QColor col) { mWhiteSquareColor=col; update();}
    void setBlackSquareColor( QColor col) {mBlackSquareColor=col; update();}
    void setWhitePieceColor( QColor col) {  mWhitePieceColor=col; update();}
    void setBlackPieceColor( QColor col) {  mBlackPieceColor=col; update(); }
    void setSideToPlayColor(QColor col)  { mSideToPlayColor=col; update();}
    void setPosition( chess::Board board) { mBoard=board;};
    QStringList listOfTypeOfPieces();
    ///
    /// \brief flipBoard Flip the board 
    /// \param flip true or false
    ///
    void flipBoard( bool flip);
    ///
    /// \brief getFEN  get the FEN of position. The FEN is a readable key allowing to
    /// retrieve a position 
    ///
    QString getFEN();
    
    ///
    /// \brief setFEN : set the Board with the FEN passed in argument
    /// 
    ///
    
    void  setFEN(QString fen);
    ///
    /// \brief AuthorizedCase return the list of autorized cases
    /// \param move the move to be played for example e2
    /// \return  d6 d5 is the case are unoccuped and no check is possible
    ///
    QStringList AuthorizedCase(QString move);
    
    
    void AskUpdate(){  update();}
     ///
    /// \brief getName return the piece with an enum WHITEPAWN etc ...
    /// \param file 
    /// \param rank
    /// \return 
    ///
    QString getName(int file, int rank);
    ///
    /// \brief setClickable if no clickabe the pieces can't be moved my mouse
    /// \param clickable
    ///
    void setClickable(bool clickable);
    ///
    /// \brief PlayListOfSANMove : this function set the  board at begining state ask to play a liste of moves in 
    ///  SAN syle ie. For example : e4 e5 Nf6 
    /// \param moves
    ///
    void PlayListOfSANMove( QStringList moves);
    ///
    /// \brief setCorrection force correction of x and y 
    /// \param x a value from 0,50 to 1,00 for x adjustement
    /// \param y a value from 0,50 to 1,00 for y adjustement
    ///
    void setCorrection(qreal x);
    
    ///
    /// \brief flipped 
    /// \return true is black are on bottom false else
    /// 

    bool flipped();
    
    ///
    /// \brief casesNumbered
    /// \return return true if columns A H and lines  1 8 are displayed
    ///
    bool casesNumbered();
    
    ///
    /// \brief askReloadConfiguration when the Config change the board is informed 
    ///        to reload all configuration informations
    /// 
    ///
    void askReloadConfiguration();
    
private:
    void RecordChessFonts();
    ///
    /// \brief mBoard is the bord frot chess library in charge of maintains the position and 
    /// all  the usefull informations 
    ///
    Board mBoard;
    ///
    /// \brief mFont is the chess font used to display the piece
    ///
    QFont mFont;
    ///
    /// \brief mColor is  QColor of the piece
    ///
    QColor mColor;
    ///
    /// \brief mFlip if flip the black side in at bottom else the white are at bottom
    ///
    bool mFlip=false;
    ///
    /// \brief mNumberedCase  on true the chess board see the A B C ... and 1 2 3 tags in border of the
    /// chess board
    ///
    bool mNumberedCase=false;
    
    int  mSize8CaseH;
    int  mSize8CaseV;
    
    /// the size of the board in pixels. Theses sizes can be corrected by mXcorrection or mYcorrection
    /// 
    int mHSizeBoard; 
    int mVSizeBoard; 
    ///
    /// \brief mA2H  numbered text is A B ... H and  1 2 ... 8 if mA2H is true else H ... A ans 8 to 1
    ///
    bool mA2H=false;   
    void paintEvent(QPaintEvent *e) override;
    ///
    /// \brief mWhiteSquareColor as usual
    ///
    QColor mWhiteSquareColor;
    QColor mBlackSquareColor;
    QColor mWhitePieceColor;
    QColor mBlackPieceColor;
    QColor mSideToPlayColor;
    
    qreal mXcorrection;
    qreal mYcorrection;
    ///
    /// \brief mTileSize is the size of a Square
    ///
    int mTilewidth;
    int mTileheight;
    ///
    /// \brief mX x and y poistion of current object
    ///
    int mX, mY;
    ///
    /// \brief mRow row and column variables
    ///
    int mRow, mCol;
    
    ///
    /// \brief mShift is a space used to separate board and A..H 1..8 
    ///
    int mShiftX;
    int mShiftY;
    ///
    /// \brief mMargin 
    ///
    int mMarginX;
    int mMarginY;

   
    QStringList mFontList;
    /// the current font used to show the pieces ...the pieces are printed as 'o' for pawn
    /// but on each font the pawn is not 'o' . we maintains a table of correspondance in the code
    /// 
    QString mCurrentFont;
    ///
    /// \brief mShowLetters if true the A ..H 1 .. 8 wil be shown
    ///
    bool mShowLetters;
    ///
    /// \brief mShowPossibleMoves if true the possible move will be shown
    ///
    bool mShowPossibleMoves;
    
    ///
    /// \brief mPossibleMoves list of possible moves recorder e3, e4 etc juste arrival square
    ///
    QStringList mPossibleMoves;
    
    
    ///
    /// \brief mClickable the chessboard can be clicked only fi mClickable is set
    ///
    bool mClickable=true;
    
    int NumberCase(int x, int y);
    ///
    /// \brief Median to be sure color object will be seen on White Squares and Black squares we calcul the median color
    /// 
    /// \param color1
    /// \param color2
    /// \return 
    ///
    QColor Median(QColor color1, QColor color2);
    ///
    /// \brief DrawPossiblesMoves draw a circle with median color to signal the possible moves of a piece
    /// \param painter
    ///
    void DrawPossiblesMoves(QPainter *painter);
    ///
    /// \brief DrawNumberedCase print the A B C D E F G H and 1 2 3 4 5 6 7 to show the case numbers
    /// \param painter
    ///
    void DrawNumberedCase(QPainter *painter);
    ///
    /// \brief DrawPieces draw the pieces 
    /// \param painter
    ///
    void DrawPiece(QPainter *painter);
    ///
    /// \brief DrawOneSquare draw a square wih Painter
    /// \param painter used in paintEvent
    /// \param x the x coordonate
    /// \param y the y 
    /// \param size the size of the square
    /// \param squarecolor the color in QColor
    ///
    void DrawOneSquare(QPainter *painter, int x, int y, int w, int h, QColor squarecolor);
    
    ///
    /// \brief mSquareToBePlayed this variable memorize the departure square before the next move is played
    /// it is initiaized with nothing 
    ///
    Square mSquareToBePlayed=Square();
    ///
    /// \brief mouse status 
    ///
    enum MouseStatus {PressedNotReleased,  PressedReleased, NotPressed} mMouseStatus=NotPressed;
    ///
    /// When you play a game in one of analyze modes or in pgn editing you can walk inside the list of moves
    QStringList mMoveUCIList;
    QStringList mMoveSanList;
    ///
    /// \brief mCurrent the current element in mMoveList. If not move is played mCurrent=-1 at first mCurrent=0 after mCurrent=1
    ///
    int mCurrent=-1;
    ///
    /// \brief isPromotion is true if  the next move is a promotion. We know next move is 
    /// a promotion because they are for example a8q a8r a8b a8n c8q c8q a8r etc ..
    /// \param possiblemove the  move 
    /// \return true if it is a promotion
    ///
    bool isPromotion(QString possiblemove);
    
    ///
    /// \brief isPromotion is true is all the moves are promotion. We know next move is 
    /// a promotion because they are for example a8q a8r a8b a8n c8q c8q a8r
    /// \param possiblemoves the list of moves. We cannot have one move that is not a promotion.
    /// \return 
    ///
    bool isPromotion (QStringList possiblemoves);

    ///
    /// \brief ListofPromotionMoves if list of move are promotion they contains
    /// moves like a8q a8r a8b a8k
    ///  Whe must delete the last letter and present a list of cases. It is not
    ///  possible to have other moves
    /// than promotions
    /// \param possibleMoves list of possible moves 4 time longuer
    /// \return the list with no doublon and no last letter
    ///
    QStringList ListofPromotionMoves(QStringList possibleMoves);
    
    
    QChar mPromotion;
    TypeMove mTypeMove;
    ///
    /// \brief DrawSideToPLay display a little marker on the board to indicate the side to play
    /// \param painter 
    ///
    void DrawSideToPlay(QPainter *painter);
    
    ///
    /// \brief mEnPassant when mouse is pressed and pawn is selected if there are an enPassant 
    /// possible move mEnPassant become true. This occurs on mousepress event and is done on mouserelease
    ///
    bool mEnPassant = false;
  
public slots:
    void setCurrentFont( QString font );
    /* to see the chesseboard from black side set reversed to true by default it is on false*/
    void setNumberCase (bool on);
    
    ///
    /// \brief goStart go to the start of the game
    ///
    void goStart();
    ///
    /// \brief gotEnd got to the end of the game
    ///
    void goEnd();
    ///
    /// \brief goBack go back 
    ///
    void goBack();
    ///
    /// \brief goNext gotNext record
    ///
    void goNext();
    
    
signals:
 //   void LenghtAndColorFromChessboard( int , QColor);
    void MovesModifiedFromChessBoard( QStringList );
    void FENFromChessBoard(QString);
protected:
    virtual void resizeEvent(QResizeEvent *e) override ;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    
};

inline bool ChessBoard::casesNumbered() { return mNumberedCase ;}

#endif // CHESSBOARD_H
