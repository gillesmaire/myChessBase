#include "formpgneditor.h"
#include "ui_formpgneditor.h"

FormPGNEditor::FormPGNEditor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormPGNEditor)
{
    ui->setupUi(this);
    connect (ui->widgetNavigation,SIGNAL(button(int)),this,SLOT(Go(int)));
}


void FormPGNEditor::Go(int i)
{
    qDebug()<<i;
}
FormPGNEditor::~FormPGNEditor()
{
    delete ui;
}
