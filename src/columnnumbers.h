#ifndef COLUMNNUMBERS_H
#define COLUMNNUMBERS_H

#include <QWidget>

class ColumnNumbers : public QWidget
{
    Q_OBJECT
public:
    explicit ColumnNumbers(QWidget *parent = nullptr);
    void setOrientation(bool a2h);
private: 
    bool ma2h;
    QColor mLetterColor;
    int mBoardLenght;
public slots: 
    void Reception( int lenght, QColor color);
protected:
    void paintEvent(QPaintEvent *)  ;
};

#endif // COLUMNNUMBERS_H
