#include "formcounterpage.h"
#include "ui_formcounterpage.h"
#include <QFontDatabase>
#include <QTimer>


FormCounterPage::FormCounterPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCounterPage)
{ 
    ui->setupUi(this);
    ui->lcdHMS->display("0:0:0");
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &FormCounterPage::updateTime);
    timer->start(1000);
}


void FormCounterPage::updateTime()
{
  if ( mReady )
  
    {   seconds++;
        int h,m,s;
        h=seconds/3600;
        m=seconds%3600;
        m=m/60;
        s=m%60;
        QString display=QString("%h:%m:%s").arg(h).arg(m).arg(s);
        ui->lcdHMS->display(display);
    }
}

FormCounterPage::~FormCounterPage()
{
    delete ui;
}

void FormCounterPage::On()
{
   mReady=true;
   ui->lcdPGN->display(0);
   ui->lcdHMS->display("0:0:0");
   seconds=0;
}

void FormCounterPage::Off()
{
    mReady=false;
}

void FormCounterPage::IncremetentConversionCounter()
{   
    int val=ui->lcdPGN->value();
    ui->lcdPGN->display(val+1);
    
}
