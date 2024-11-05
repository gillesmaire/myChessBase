#include "dialogconfiguration.h"
#include "ui_dialogconfiguration.h"

DialogConfiguration::DialogConfiguration(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogConfiguration)
{
    ui->setupUi(this);
    ui->pushButtonBlackPieceColor->setName("BlackPieceColor");
    ui->pushButtonWhitePieceColor->setName("WhitePieceColor");
    ui->pushButtonBlackSquareColor->setName("BlackSquareColor");
    ui->pushButtonWhiteSquareColor->setName("WhiteSquareColor");
    connect (ui->pushButtonBlackPieceColor,SIGNAL(ColorChanged(QString,QColor)),this,SLOT(ChangeColor(QString,QColor)));
    connect (ui->pushButtonBlackSquareColor,SIGNAL(ColorChanged(QString,QColor)),this,SLOT(ChangeColor(QString,QColor)));
    connect (ui->pushButtonWhitePieceColor,SIGNAL(ColorChanged(QString,QColor)),this,SLOT(ChangeColor(QString,QColor)));
    connect (ui->pushButtonWhiteSquareColor,SIGNAL(ColorChanged(QString,QColor)),this,SLOT(ChangeColor(QString,QColor)));
}

DialogConfiguration::~DialogConfiguration()
{
    delete ui;
}

void DialogConfiguration::ChangeColor(QString string,QColor color)
{
 if ( string == "BlackSquareColor" ) ui->widget->setBlackSquareColor(color);
 else if ( string == "WhiteSquareColor" ) ui->widget->setWhiteSquareColor(color);
}
