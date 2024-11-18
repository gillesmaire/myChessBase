#ifndef PIECE_H
#define PIECE_H
#include <QObject>
#include <QFont>
#include <QColor>
#include <QPoint>

class piece 
{
public:
    explicit piece(QString piecename, QChar character);
    QString getPieceName(){return mPieceName;}
    QString getCharacter(){return mCharacter;}
private:
    QString mPieceName;
    QChar mCharacter;
    QPoint mOffset; 
    
};


#endif // PIECE_H
