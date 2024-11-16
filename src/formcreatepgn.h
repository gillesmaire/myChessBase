#ifndef FORMCREATEPGN_H
#define FORMCREATEPGN_H

#include <QWidget>

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
};

#endif // FORMCREATEPGN_H
