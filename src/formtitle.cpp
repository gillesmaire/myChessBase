#include "formtitle.h"
#include "ui_formtitle.h"

FormTitle::FormTitle(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormTitle)
{
    ui->setupUi(this);
}

FormTitle::~FormTitle()
{
    delete ui;
}

void FormTitle::setTitle( QString title)
{
if (title.length()>70) title.insert(70,"\n");

ui->label->setText(title);
}
