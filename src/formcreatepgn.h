#ifndef FORMCREATEPGN_H
#define FORMCREATEPGN_H

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

private:
    Ui::FormCreatePGN *ui;
    void GoIndex0();
    QStackedWidget *mStackedWidget;
    void Reset();
    void FormAutoFillBlack();
    void FormAutoFillWhite();
};

#endif // FORMCREATEPGN_H
