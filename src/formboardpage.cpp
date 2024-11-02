#include "formboardpage.h"
#include "ui_formboardpage.h"

FormBoardPage::FormBoardPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormBoardPage)
{
    ui->setupUi(this);
}

FormBoardPage::~FormBoardPage()
{
    delete ui;
}
