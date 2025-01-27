#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include "chess.hpp"
#include <QMap>
#include "movablePiece.h"
 using namespace chess;



typedef enum {PossibleMoves,LastMove,Nothing}  Raison;


class ChessBoard : public QWidget
{
     Q_OBJECT
public:
    explicit ChessBoard(QWidget *widget);
    void setWhiteSquareColor( QColor col) { mWhiteSquareColor=col; update();}
    void setBlackSquareColor( QColor col) {mBlackSquareColor=col; update();}
    void setWhitePieceColor( QColor col) {  mWhitePieceColor=col; update();}
    void setBlackPieceColor( QColor col) {  mBlackPieceColor=col; update(); }
    void setPosition( chess::Board board) { mBoard=board;};
    QStringList listOfTypeOfPieces();
    void flipBoard( bool flip){ mFlip=flip; update();}
    QString getFEN();
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
    void setCorrection(qreal x, qreal y);

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
    
    qreal mXcorrection;
    qreal mYcorrection;
    ///
    /// \brief mTileSize is the size of a Square
    ///
    int mTilewith;
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
    /// \brief Debug display the board in ASCII mode 
    /// 
    ///
    void Debug();
    
    ///
    /// When you play a game in one of analyze modes or in pgn editing you can walk inside the list of moves
    QStringList mMoveUCIList;
    QStringList mMoveSanList;
    ///
    /// \brief mCurrent the current element in mMoveList. If not move is playe mCurrent=-1 at first mCurrent=0 after mCurrent=1
    ///
    int mCurrent=-1;
    
   
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
    void LenghtAndColor( int , QColor);
    void MovesModified( QStringList );
protected:
    virtual void resizeEvent(QResizeEvent *e) override ;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    
};

#endif // CHESSBOARD_H
