#include "dialogconfiguration.h"
#include "ui_dialogconfiguration.h"
#include <QSettings>

extern QString InitWhiteSquareColor;
extern QString InitBlackSquareColor;
extern QString InitWhitePieceColor;
extern QString InitBlackPieceColor;
   
DialogConfiguration::DialogConfiguration(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogConfiguration)
{
    ui->setupUi(this);
    QSettings s;
    ui->pushButtonBlackPieceColor->setName("BlackPieceColor");
    ui->pushButtonBlackPieceColor->setColor(s.value("BlackPieceColor",InitBlackPieceColor).toString());
    ui->pushButtonWhitePieceColor->setName("WhitePieceColor");
    ui->pushButtonWhitePieceColor->setColor(s.value("WhitePieceColor",InitWhitePieceColor).toString());
    ui->pushButtonBlackSquareColor->setName("BlackSquareColor");
    ui->pushButtonBlackSquareColor->setColor(s.value("BlackSquareColor",InitBlackSquareColor).toString());
    ui->pushButtonWhiteSquareColor->setName("WhiteSquareColor");
    ui->pushButtonWhiteSquareColor->setColor(s.value("WhiteSquareColor",InitWhiteSquareColor).toString());
    ui->lineEditYourFirstname->setText(s.value("YourFirstname").toString());
    ui->lineEditYourName->setText(s.value("YourName").toString());
    ui->lineEditYourFideID->setText(s.value("YourFideID").toString());
    ui->lineEditYourTitle->setText(s.value("YourTitle").toString());
    ui->lineEditYourELO->setText(s.value("YourELO").toString());
    ui->comboBoxPieces->addItems(ui->widget->listOfTypeOfPieces());
    
    ui->comboBoxPieces->setCurrentText(s.value("PiecesFont").toString());
    
    connect (ui->pushButtonBlackPieceColor,SIGNAL(ColorChanged(QString,QColor)),this,SLOT(ChangeColor(QString,QColor)));
    connect (ui->pushButtonBlackSquareColor,SIGNAL(ColorChanged(QString,QColor)),this,SLOT(ChangeColor(QString,QColor)));
    connect (ui->pushButtonWhitePieceColor,SIGNAL(ColorChanged(QString,QColor)),this,SLOT(ChangeColor(QString,QColor)));
    connect (ui->pushButtonWhiteSquareColor,SIGNAL(ColorChanged(QString,QColor)),this,SLOT(ChangeColor(QString,QColor)));
    connect (ui->pushButtonCloseBoard,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect (ui->pushButtonSaveBoard,SIGNAL(clicked(bool)),this,SLOT(Save()));
    connect (ui->comboBoxPieces,SIGNAL(currentTextChanged(QString)),this,SLOT(ChangePiece(QString)));
    connect (ui->pushButtonCloseInformations,&QPushButton::clicked,this,&DialogConfiguration::close);
    connect (ui->pushButtonSaveBoard,&QPushButton::clicked,this,&DialogConfiguration::Save);
    connect (ui->pushButtonValidateInformations,&QPushButton::clicked,this,&DialogConfiguration::SaveInformations);
}

DialogConfiguration::~DialogConfiguration()
{
    delete ui;
}

void DialogConfiguration::ChangeColor(QString string,QColor color)
{
 if ( string == "BlackSquareColor" ) ui->widget->setBlackSquareColor(color);
 else if ( string == "WhiteSquareColor" )ui->widget->setWhiteSquareColor(color);
 else if ( string == "BlackPieceColor" ) ui->widget->setBlackPieceColor(color);
 else if ( string == "WhitePieceColor" ) ui->widget->setWhitePieceColor(color);
 
}

void DialogConfiguration::Save()
{
    QSettings s;
    s.setValue("BlackSquareColor",ui->pushButtonBlackSquareColor->getColor());
    s.setValue("WhiteSquareColor",ui->pushButtonWhiteSquareColor->getColor());
    s.setValue("BlackPieceColor",ui->pushButtonBlackPieceColor->getColor());
    s.setValue("WhitePieceColor",ui->pushButtonWhitePieceColor->getColor());
    s.setValue("PiecesFont",ui->comboBoxPieces->currentText());
    emit askRefresh();
}

void DialogConfiguration::ChangePiece(QString name)
{
    ui->widget->setCurrentFont(name);
}

void DialogConfiguration::SaveInformations()
{
    QSettings s;
    s.setValue("YourFirstname",ui->lineEditYourFirstname->text());
    s.setValue("YourName",ui->lineEditYourName->text());
    s.setValue("YourELO",ui->lineEditYourELO->text());
    s.setValue("YourFideID",ui->lineEditYourFideID->text());
    s.setValue("YourTitle",ui->lineEditYourTitle->text());    
}


