#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include "chess.hpp"
#include <QMap>

class ChessBoard : public QWidget
{
public:
    explicit ChessBoard(QWidget *widget);
    void setWhiteSquareColor( QColor col) { mWhiteSquareColor=col; update();}
    void setBlackSquareColor( QColor col) { mBlackSquareColor=col; update();}
    void setWhitePieceColor( QColor col) {  mWhitePieceColor=col; update(); }
    void setBlackPieceColor( QColor col) {  mBlackPieceColor=col; update(); }
    void setPosition( chess::Board board) { mBoard=board;};
    QStringList listOfTypeOfPieces();
private: 
    void RecordChessFonts();
    chess::Board mBoard;
    int mSize;
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
public slots:
    void setCurrentFont( QString font );
signals:
protected:
    void resizeEvent(QResizeEvent *e) override ;
};

#endif // CHESSBOARD_H
