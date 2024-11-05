#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include "chess.hpp"

class ChessBoard : public QWidget
{
public:
    explicit ChessBoard(QWidget *widget);
    void setWhiteSquareColor( QColor col) { mWhiteSquareColor=col; update();}
    void setBlackSquareColor( QColor col) { mBlackSquareColor=col; update();}
private: 
    chess::Board mBoard;
    int mSize;
    void paintEvent(QPaintEvent *e) override;
    QColor mWhiteSquareColor;
    QColor mBlackSquareColor;
signals:
protected:
    void resizeEvent(QResizeEvent *e) override ;
};

#endif // CHESSBOARD_H
