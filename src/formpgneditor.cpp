#include "formpgneditor.h"
#include "ui_formpgneditor.h"
#include "utils.h"
#include <QDate>
#include <QSettings>

FormPGNEditor::FormPGNEditor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormPGNEditor)
{
    ui->setupUi(this);
    ui->comboBoxResult->setCurrentText("?");
    QDate today=QDate::currentDate();
    ui->spinBoxDay->setMaximum(31); 
    ui->spinBoxDay->setMinimum(1);
    ui->spinBoxDay->setValue(today.day());
    ui->spinBoxMonth->setMaximum(12);
    ui->spinBoxMonth->setMinimum(1);
    ui->spinBoxMonth->setValue(today.month());
    ui->spinBoxYear->setMinimum(1600);
    ui->spinBoxYear->setMaximum(today.year());
    ui->spinBoxYear->setValue(today.year());
 
    connect(ui->pushButtonReset,&QPushButton::clicked,this,&FormPGNEditor::Reset);
    connect(ui->pushButtonBlackYou,&QPushButton::clicked,this,&FormPGNEditor::FormAutoFillBlack);
    connect(ui->pushButtonWhiteYou,&QPushButton::clicked,this,&FormPGNEditor::FormAutoFillWhite);
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

QString FormPGNEditor::getListMove() 
{
    return ui->textEditMoves->toPlainText();
}

void FormPGNEditor::SetListMove(QString listmove)
{
    ui->textEditMoves->clear();
    ui->textEditMoves->setText(Utils::NumberSanMoves(listmove.split(" ")));
}


void FormPGNEditor::Reset()
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
 
 // ui->dateEdit->setDate(QDate::currentDate());
  ui->lineEditSite->clear();
  ui->lineEditRound->clear();
}

void FormPGNEditor::FormAutoFillBlack() 
{
    QSettings s;
    ui->lineEditBlackELO->setText(s.value("YourELO").toString());
    ui->lineEditBlackFIDEID->setText(s.value("YourFideID").toString());
    ui->lineEditBlackName->setText(s.value("YourName").toString()+","+s.value("YourFirstname").toString());
    ui->lineEditBlackTitle->setText(s.value("YourTitle").toString());
}

void FormPGNEditor::FormAutoFillWhite()
{
    QSettings s;
    ui->lineEditWhiteELO->setText(s.value("YourELO").toString());
    ui->lineEditWhiteFIDEID->setText(s.value("YourFideID").toString());
    ui->lineEditWhiteName->setText(s.value("YourName").toString()+","+s.value("YourFirstname").toString());
    ui->lineEditWhiteTitle->setText(s.value("YourTitle").toString());
}
