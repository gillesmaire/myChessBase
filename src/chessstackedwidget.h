#ifndef CHESSSTACKEDWIDGET_H
#define CHESSSTACKEDWIDGET_H

#include <QStackedWidget>

class ChessStackedWidget : public  QStackedWidget
{
public:
    ChessStackedWidget( QWidget *parent);
    void close ();
    
};

#endif // CHESSSTACKEDWIDGET_H
