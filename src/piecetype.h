#ifndef PIECETYPE_H
#define PIECETYPE_H

#include <QObject>
#include <QFont>
#include <QColor>
#include <QPoint>

class PieceType : public QObject
{
    Q_OBJECT
public:
    explicit PieceType(QObject *parent = nullptr);
private:
    QString mFontName;
    QString mUserName;
    QPoint mOffset; 
};

     

#endif // PIECETYPE_H
