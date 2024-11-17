#include "formcreatepgn.h"
#include "ui_formcreatepgn.h"
#include <QDebug>
#include <QSettings>

FormCreatePGN::FormCreatePGN(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormCreatePGN)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    connect(ui->pushButtonClose,&QPushButton::clicked,this,&FormCreatePGN::GoIndex0);
    connect(ui->pushButtonReset,&QPushButton::clicked,this,&FormCreatePGN::Reset);
    connect(ui->pushButtonBlackYou,&QPushButton::clicked,this,&FormCreatePGN::FormAutoFillBlack);
    connect(ui->pushButtonWhiteYou,&QPushButton::clicked,this,&FormCreatePGN::FormAutoFillWhite);
}

void FormCreatePGN::GoIndex0()
{
   QStackedWidget* stackedWidget = qobject_cast<QStackedWidget*>(parent());
   stackedWidget->setCurrentIndex(0);
}
FormCreatePGN::~FormCreatePGN()
{
    delete ui;
}

void FormCreatePGN::Reset()
{
  ui->lineEditBlackELO->clear();
  ui->lineEditBlackFIDEID->clear();
  ui->lineEditBlackName->clear();
  ui->lineEditBlackELO->clear();
  ui->lineEditBlackTitle->clear();
  
  ui->lineEditWhiteTitle->clear();
  ui->lineEditWhiteFIDEID->clear();
  ui->labelWhiteFIDEID->clear();
  ui->lineEditWhiteELO->clear();
  ui->lineEditWhiteName->clear();
  
  ui->textEditMoves->clear();
  ui->comboBoxResult->setCurrentIndex(0);
  ui->lineEditECO->clear();
  ui->lineEditEvent->clear();
  ui->dateEdit->setDate(QDate::currentDate());
  ui->lineEditSite->clear();
  ui->lineEditRound->clear();
}

void FormCreatePGN::FormAutoFillBlack()
{
    QSettings s;
    ui->lineEditBlackELO->setText(s.value("YourELO").toString());
    ui->lineEditBlackFIDEID->setText(s.value("YourFideID").toString());
    ui->lineEditBlackName->setText(s.value("YourName").toString()+","+s.value("YourFirstname").toString());
    ui->lineEditBlackTitle->setText(s.value("YourTitle").toString());
}

void FormCreatePGN::FormAutoFillWhite()
{
    QSettings s;
    ui->lineEditWhiteELO->setText(s.value("YourELO").toString());
    ui->lineEditWhiteFIDEID->setText(s.value("YourFideID").toString());
    ui->lineEditWhiteName->setText(s.value("YourName").toString()+","+s.value("YourFirstname").toString());
    ui->lineEditWhiteTitle->setText(s.value("YourTitle").toString());
}
