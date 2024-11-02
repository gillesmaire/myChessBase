#include "dialogabout.h"
#include "ui_dialogabout.h"

DialogAbout::DialogAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAbout)
{
    ui->setupUi(this);
   connect (ui->pushButtonClose,&QPushButton::clicked,this,&DialogAbout::close);
}

DialogAbout::~DialogAbout()
{
    delete ui;
}

