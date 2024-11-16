#include "formcreatepgn.h"
#include "ui_formcreatepgn.h"

FormCreatePGN::FormCreatePGN(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormCreatePGN)
{
    ui->setupUi(this);
}

FormCreatePGN::~FormCreatePGN()
{
    delete ui;
}
