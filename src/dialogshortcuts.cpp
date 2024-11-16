#include "dialogshortcuts.h"
#include "ui_dialogshortcuts.h"

DialogShortCuts::DialogShortCuts(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogShortCuts)
{
    ui->setupUi(this);
}

DialogShortCuts::~DialogShortCuts()
{
    delete ui;
}
