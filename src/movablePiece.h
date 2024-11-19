#ifndef MOVABLEPIECE_H
#define MOVABLEPIECE_H
#include <QWidget>
#include <QFont>
#include <QColor>
#include <QPoint>
#include <QMouseEvent>

class movablePiece : public QWidget
{
public:
    explicit movablePiece(QString piecename, QChar character, QWidget *parent );
    QString getPieceName(){return mPieceName;}
    QString getCharacter(){return mCharacter;}
private:
    QString mPieceName;
    QChar mCharacter;
    QPoint mOffset; 
    QString FontName;
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    //https://stackoverflow.com/questions/11172420/moving-object-with-mouse
};


#endif // MOVABLEPIECE_H
