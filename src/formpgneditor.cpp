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
    connect(ui->pushButtonReset,&QPushButton::clicked,this,&FormPGNEditor::Reset);
    connect(ui->pushButtonBlackYou,&QPushButton::clicked,this,&FormPGNEditor::FormAutoFillBlack);
    connect(ui->pushButtonWhiteYou,&QPushButton::clicked,this,&FormPGNEditor::FormAutoFillWhite);
    connect (ui->widgetNavigation,SIGNAL(button(int)),this,SLOT(Go(int)));
    connect (ui->pushButtonEraseWhitePlayer,&QPushButton::clicked,this,&FormPGNEditor::EraseWhitePlayer);
    connect (ui->pushButtonEraseBlackPlayer,&QPushButton::clicked,this,&FormPGNEditor::EraseBlackPlayer);
}


void FormPGNEditor::Go(int i)
{
    if ( i == FormNavigationButton::First ) ui->Board->goStart();
    else if (i == FormNavigationButton::Last ) ui->Board->goEnd();
    else if (i == FormNavigationButton::Before ) ui->Board->goBack();
    else if (i == FormNavigationButton::Next ) ui->Board->goNext();
    else if (i== FormNavigationButton::Reverse) ui->Board->flipBoard(!ui->Board->flipped());
    else if (i== FormNavigationButton::NumberCase) ui->Board->setNumberCase(!ui->Board->casesNumbered());
    else  if (i== FormNavigationButton::FEN){ emit showFen();}
    
}

FormPGNEditor::~FormPGNEditor()
{
    delete ui;
}

QString FormPGNEditor::getListMove() 
{
    return ui->textEditMoves->toPlainText();
}

void FormPGNEditor::EraseBlackPlayer() 
{
    ui->lineEditBlackFirstName->clear();
    ui->lineEditBlackName->clear();
    ui->spinBoxBlackElo->setValue(0);
    ui->SpinBoxBlackFideID->setValue(0);
    ui->comboBoxBlackTitle->setCurrentIndex(0);

}

void FormPGNEditor::EraseWhitePlayer() 
{
    ui->lineEditWhiteFirstName->clear();
    ui->lineEditWhiteName->clear();
    ui->spinBoxWhiteElo->setValue(0);
    ui->spinBoxWhiteFideID->setValue(0);
    ui->comboBoxBlackTitle->setCurrentIndex(0);
}

void FormPGNEditor::SetListMove(QString listmove)
{
    ui->textEditMoves->clear();
    ui->textEditMoves->setText(Utils::NumberSanMoves(listmove.split(" ")));
}


void FormPGNEditor::Reset()
{
  ui->spinBoxBlackElo->setValue(0);
  ui->SpinBoxBlackFideID->setValue(0);
  ui->lineEditBlackFirstName->clear();
  ui->lineEditBlackName->clear();
  ui->spinBoxBlackElo->setValue(0);
  ui->comboBoxBlackTitle->setCurrentIndex(0);
  
  
  ui->spinBoxWhiteElo->setValue(0);
  ui->spinBoxWhiteFideID->setValue(0);
  ui->lineEditWhiteFirstName->clear();
  ui->lineEditWhiteName->clear();
  ui->spinBoxWhiteElo->setValue(0);
   ui->comboBoxWhiteTitle->setCurrentIndex(0);
 
  
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
    ui->spinBoxBlackElo->setValue(s.value("YourELO").toInt());
    ui->SpinBoxBlackFideID->setValue(s.value("YourFideID").toInt());
    ui->lineEditBlackFirstName->setText(s.value("YourFirstname").toString());
    ui->lineEditBlackName->setText(s.value("YourName").toString());
    ui->comboBoxBlackTitle->setCurrentText(s.value("YourTitle").toString());
}

void FormPGNEditor::FormAutoFillWhite()
{
    QSettings s;
    ui->spinBoxWhiteElo->setValue(s.value("YourELO").toInt());
    ui->spinBoxWhiteFideID->setValue(s.value("YourFideID").toInt());
    ui->lineEditWhiteFirstName->setText(s.value("YourFirstname").toString());
    ui->lineEditWhiteName->setText(s.value("YourName").toString());
    ui->comboBoxWhiteTitle->setCurrentText(s.value("YourTitle").toString());
}

