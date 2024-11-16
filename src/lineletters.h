#ifndef LINELETTERS_H
#define LINELETTERS_H

#include <QWidget>

class LineLetters : public QWidget
{
    Q_OBJECT
public:
    explicit LineLetters(QWidget *parent = nullptr);
    void setOrientation( bool a2h );
    
private :
    bool ma2h;
    QColor mLetterColor;
    int mBoardLenght;
    
public slots: 
    void Reception( int lenght, QColor color);
protected:
    void paintEvent(QPaintEvent *)  ;

};

#endif // LINELETTERS_H
