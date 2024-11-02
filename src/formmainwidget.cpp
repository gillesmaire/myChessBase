#include "formmainwidget.h"
#include "ui_formmainwidget.h"

FormMainWidget::FormMainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormMainWidget)
{
    ui->setupUi(this);
}

FormMainWidget::~FormMainWidget()
{
    delete ui;
}
