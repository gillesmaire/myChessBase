#ifndef UNIVERSPGN_H
#define UNIVERSPGN_H

#include <QWidget>
#include "chessstackedwidget.h"

namespace Ui {
class FormCreatePGN;
}

class FormCreatePGN : public QWidget
{
    Q_OBJECT

public:
    explicit FormCreatePGN(QWidget *parent = nullptr);
    ~FormCreatePGN();
    void SetListMove(QString);
    ///
    /// \brief getListMove return the text in que QTexEdit ie list of moves
    /// \return 
    ///
    QString getListMove();
private:
    Ui::FormCreatePGN *ui;
    void GoIndex0();
    QStackedWidget *mStackedWidget;
    void Reset();
    void FormAutoFillBlack();
    void FormAutoFillWhite();
private slots:
    void GetListMoves(QStringList list); 
};

#endif // UNIVERSPGN_H
