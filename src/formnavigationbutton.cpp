#include "formnavigationbutton.h"
#include "ui_formnavigationbutton.h"
#include <QResizeEvent>
#include <QTimer>
#include <QSettings>

FormNavigationButton::FormNavigationButton(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormNavigationButton)
{
    ui->setupUi(this);
    connect (ui->pushButtonFirst,&QPushButton::clicked,this,&FormNavigationButton::dispatch);
    connect (ui->pushButtonBefore,&QPushButton::clicked,this,&FormNavigationButton::dispatch);
    connect (ui->pushButtonNext,&QPushButton::clicked,this,&FormNavigationButton::dispatch);
    connect (ui->pushButtonLast,&QPushButton::clicked,this,&FormNavigationButton::dispatch);
    connect (ui->pushButtonReverse,&QPushButton::clicked,this,&FormNavigationButton::dispatch);
    connect (ui->pushButtonNumberCase,&QPushButton::clicked,this,&FormNavigationButton::dispatch);
    connect (ui->pushButtonFEN,&QPushButton::clicked,this,&FormNavigationButton::dispatch);
    connect (ui->pushButtonPlay,&QPushButton::clicked,this,&FormNavigationButton::dispatch);
    mTimer = new QTimer(this);
    connect(mTimer, &QTimer::timeout, this,&FormNavigationButton::AutoPlay);
  

}


void FormNavigationButton::dispatch()
{
   QString origin=sender()->objectName();
   if (  origin.endsWith("First")) emit button(Action::First) ;
   else if ( origin.endsWith("Last") ) emit button(Action::Last) ;
   else if ( origin.endsWith("Next") ) emit button(Action::Next) ;
   else if ( origin.endsWith("Play") ) AutoPlay();
   else if ( origin.endsWith("Before") ) emit button(Action::Before) ;
   else if ( origin.endsWith("Reverse") ) emit button(Action::Reverse) ;
   else if ( origin.endsWith("NumberCase") ) emit button(Action::NumberCase) ;
   else if ( origin.endsWith("RemoveLast") ) emit button(Action::RemoveLast) ;
   else if ( origin.endsWith("FEN") ) emit button(Action::FEN) ;
   else emit button(Action::First);
}

void FormNavigationButton::modePause(bool mode)
{
    if ( mode )
       mTimer->stop();
    else 
       mTimer->start(50*(speed+1));
}

void FormNavigationButton::resizeEvent(QResizeEvent *) 
{
}

void FormNavigationButton::SetUnsetPlayButton( bool empty) {
    ui->pushButtonPlay->setEnabled(!empty);
}

FormNavigationButton::~FormNavigationButton()
{
    delete ui;
}

void FormNavigationButton::AutoPlay()
{
    QSettings s;
    emit button(Action::Play);
    emit button(Action::Next);  
    int spm=250*(s.value("SpeedMove",4).toInt()+1);
    mTimer->start(spm);
}

void FormNavigationButton::ChangeSpeed(int speed)
{
    mTimer->stop();
    mTimer->start(250*(speed+1));
}
