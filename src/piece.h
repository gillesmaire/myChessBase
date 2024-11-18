#ifndef PIECE_H
#define PIECE_H
#include "piecetype.h"
#include <QObject>
#include <QFont>
#include <QColor>
#include <QPoint>

class Piece : public PieceType
{
    Q_OBJECT
public:
    explicit Piece(QString piece, QChar c, QColor cback , QColor cfront);
private:
    QString mPieceName;
    QChar mCharacter;
    QPoint mOffset; 
    QColor mColor;
};

     
};

#endif // PIECE_H
