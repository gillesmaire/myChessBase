#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include "chess.hpp"
#include <QMap>
 using namespace chess;

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
private: 
    void RecordChessFonts();
    Board mBoard;
    bool mFlip=false;
    bool mNumberedCase=false;
    int mSizeBoard; // size of board
    bool mA2H=false;   // numbered text is A B ... H and  1 2 ... 8 if mA2H is true else H ... A ans 8 to 1
    void paintEvent(QPaintEvent *e) override;
    QColor mWhiteSquareColor;
    QColor mBlackSquareColor;
    QColor mWhitePieceColor;
    QColor mBlackPieceColor;
    QString getName(int row, int col);
    QMap<QString,QMap<QString,QChar>> mChessFonts;
    QMap <QString,QString> mFontName;
    QStringList mFontList;
    QString mCurrentFont;
    bool mShowLetters;
    //bool mReversed=false;
public slots:
    void setCurrentFont( QString font );
    /* to see the chesseboard from black side set reversed to true by default it is on false*/
    void setNumberCase (bool on);
signals:
    void LenghtAndColor( int , QColor);
protected:
    void resizeEvent(QResizeEvent *e) override ;
};

#endif // CHESSBOARD_H
