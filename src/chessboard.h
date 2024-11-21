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
    void AskUpdate(){ update();}
     ///
    /// \brief getName return the piece with an enum WHITEPAWN etc ...
    /// \param file 
    /// \param rank
    /// \return 
    ///
    QString getName(int file, int rank);
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
    /// the size of the board in pixels
    int mSizeBoard; 
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
    ///
    /// \brief mTileSize is the size of a Square
    ///
    int mTileSize;
    ///
    /// \brief mX x and y poistion of current obect
    ///
    int mX, mY;
    ///
    /// \brief mRow row and column variables
    ///
    int mRow, mCol;
    
    ///
    /// \brief mShift is a space used to separate board and A..H 1..8 
    ///
    int mShift;
    ///
    /// \brief mMargin 
    ///
    int mMargin;
    ///
    /// \brief mSize8Case size of B cases without margin or number
    ///
    int mSize8Case;
   
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
    
    void DrawOneSquare(QPainter *painter, int x, int y, int size, QColor squarecolor);
    
    Square mSquareToBePlayed=Square();
    
    void Debug();
public slots:
    void setCurrentFont( QString font );
    /* to see the chesseboard from black side set reversed to true by default it is on false*/
    void setNumberCase (bool on);
    
   
    
signals:
    void LenghtAndColor( int , QColor);
protected:
    void resizeEvent(QResizeEvent *e) override ;
    virtual void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // CHESSBOARD_H
