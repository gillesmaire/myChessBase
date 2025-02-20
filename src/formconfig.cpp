#include "formconfig.h"
#include "ui_formconfig.h"
#include <QSettings>

extern QString InitWhiteSquareColor;
extern QString InitBlackSquareColor;
extern QString InitWhitePieceColor;
extern QString InitBlackPieceColor;
extern QString InitSideToPlayColor;

FormConfig::FormConfig(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormConfig)
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
    ui->pushButtonSidetoPlayColor->setName("SideToPlayColor");
    ui->pushButtonSidetoPlayColor->setColor(s.value("SideToPlayColor",InitSideToPlayColor).toString());
    
    ui->lineEditYourFirstname->setText(s.value("YourFirstname").toString());
    ui->lineEditYourName->setText(s.value("YourName").toString());
    ui->spinBoxYourElo->setDigitNumber(4);
    ui->spinBoxFideID->setValue(s.value("YourFideID").toInt());
    ui->comboBoxYoutTitle->setCurrentText(s.value("YourTitle").toString());
    ui->spinBoxYourElo->setValue(s.value("YourELO").toInt());
    ui->comboBoxPieces->addItems(ui->widget->listOfTypeOfPieces());
    ui->doubleSpinBoxXshift->setValue(s.value("XShift",1).toDouble());
    ui->comboBoxPieces->setCurrentText(s.value("PiecesFont").toString());
    ui->widget->setClickable(false);
    
    connect (ui->pushButtonBlackPieceColor,SIGNAL(ColorChanged(QString,QColor)),this,SLOT(ChangeColor(QString,QColor)));
    connect (ui->pushButtonBlackSquareColor,SIGNAL(ColorChanged(QString,QColor)),this,SLOT(ChangeColor(QString,QColor)));
    connect (ui->pushButtonWhitePieceColor,SIGNAL(ColorChanged(QString,QColor)),this,SLOT(ChangeColor(QString,QColor)));
    connect (ui->pushButtonWhiteSquareColor,SIGNAL(ColorChanged(QString,QColor)),this,SLOT(ChangeColor(QString,QColor)));
    connect (ui->pushButtonSidetoPlayColor,SIGNAL(ColorChanged(QString,QColor)),this,SLOT(ChangeColor(QString,QColor)));
    connect (ui->pushButtonSaveBoard,SIGNAL(clicked(bool)),this,SLOT(Save()));
    
    connect (ui->comboBoxPieces,SIGNAL(currentTextChanged(QString)),this,SLOT(ChangePiece(QString)));
    connect (ui->pushButtonSaveBoard,&QPushButton::clicked,this,&FormConfig::Save);
    connect (ui->pushButtonValidateInformations,&QPushButton::clicked,this,&FormConfig::SaveInformations);
    connect (ui->doubleSpinBoxXshift,&QDoubleSpinBox::valueChanged,this,&FormConfig::RedrawChessBoard);

}

FormConfig::~FormConfig()
{
    delete ui;
}

void FormConfig::RedrawChessBoard()
{
    ui->widget->setCorrection(ui->doubleSpinBoxXshift->value());
    ui->widget->repaint();
}

void FormConfig::ChangeColor(QString string,QColor color)
{
     if ( string == "BlackSquareColor" ) ui->widget->setBlackSquareColor(color);
    else if ( string == "WhiteSquareColor" )ui->widget->setWhiteSquareColor(color);
    else if ( string == "BlackPieceColor" ) ui->widget->setBlackPieceColor(color);
    else if ( string == "WhitePieceColor" ) ui->widget->setWhitePieceColor(color);
    else if (string == "SideToPlayColor") ui->widget->setSideToPlayColor(color);
 
}

void FormConfig::Save()
{
    QSettings s;
    s.setValue("BlackSquareColor",ui->pushButtonBlackSquareColor->getColor());
    s.setValue("WhiteSquareColor",ui->pushButtonWhiteSquareColor->getColor());
    s.setValue("BlackPieceColor",ui->pushButtonBlackPieceColor->getColor());
    s.setValue("WhitePieceColor",ui->pushButtonWhitePieceColor->getColor());
    s.setValue("SideToPlayColor",ui->pushButtonSidetoPlayColor->getColor());
    s.setValue("PiecesFont",ui->comboBoxPieces->currentText());
    s.setValue("XShift",ui->doubleSpinBoxXshift->value());
    emit askRefresh();
}

void FormConfig::ChangePiece(QString name)
{
    ui->widget->setCurrentFont(name);
}

void FormConfig::SaveInformations()
{
    QSettings s;
    s.setValue("YourFirstname",ui->lineEditYourFirstname->text());
    s.setValue("YourName",ui->lineEditYourName->text());
    s.setValue("YourELO",ui->spinBoxYourElo->value());
    s.setValue("YourFideID",ui->spinBoxFideID->value());
    s.setValue("YourTitle",ui->comboBoxYoutTitle->currentText());    
}
