#include "dialogprogressbarimport.h"
#include "ui_dialogprogressbarimport.h"


DialogProgressBarImport::DialogProgressBarImport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogProgressBarImport)
{
    ui->setupUi(this);
    mTimer = new QTimer(this);
    
    connect(mTimer, &QTimer::timeout, this, &DialogProgressBarImport::ClockIncrement);
    mTimer->start(1000);
    ui->lcdChrono->display(QString("%1:%2:%3").arg("00").arg("00").arg("00"));
}

DialogProgressBarImport::~DialogProgressBarImport()
{
    delete ui;
}

void DialogProgressBarImport::CountIncrement()
{
    int c=ui->lcdCount->value()+1;
    ui->lcdCount->display(c);
    QCoreApplication::processEvents();
}

void DialogProgressBarImport::ClockIncrement()
{
   mTime++;
   int h,m,s,r;
   s=mTime%60;
   r=mTime/60;
   m=r%60;
   h=r/60;
   qDebug()<<h<<m<<s;
   QString H,M,S;
   H=QString("%1").arg(h);
   M=QString("%1").arg(m);
   S=QString("%1").arg(s);
   if (h<10) H="0"+H;
   if (m<10) M="0"+M;
   if (s<10) S="0"+S;
   ui->lcdChrono->display(QString("%1:%2:%3").arg(H).arg(M).arg(S));
   
}

void DialogProgressBarImport::ClockStop()
{
    mTimer->disconnect();
    mTimer->stop();
    delete(mTimer);
}
