#include "formnavigationbutton.h"
#include "ui_formnavigationbutton.h"
#include <QResizeEvent>

FormNavigationButton::FormNavigationButton(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormNavigationButton)
{
    ui->setupUi(this);
    connect (ui->pushButtonFirst,&QPushButton::clicked,this,&FormNavigationButton::dispatch);
    connect (ui->pushButtonBefore,&QPushButton::clicked,this,&FormNavigationButton::dispatch);
    connect (ui->pushButtonNext,&QPushButton::clicked,this,&FormNavigationButton::dispatch);
    connect (ui->pushButtonLast,&QPushButton::clicked,this,&FormNavigationButton::dispatch);
}


void FormNavigationButton::dispatch()
{
   QString origin=sender()->objectName();
   if (  origin.endsWith("First")) emit button(Action::First) ;
   else if ( origin.endsWith("Last") ) emit button(Action::Last) ;
   else if ( origin.endsWith("Next") ) emit button(Action::Next) ;
   else if ( origin.endsWith("Play") ) emit button(Action::Play) ;
   else if ( origin.endsWith("Before") ) emit button(Action::Before) ;
   else if ( origin.endsWith("Reverse") ) emit button(Action::Reverse) ;
   else if ( origin.endsWith("NumberCase") ) emit button(Action::NumberCase) ;
   else emit button(Action::First);
}


FormNavigationButton::~FormNavigationButton()
{
    delete ui;
}
