#include "dialogconfiguration.h"
#include "ui_dialogconfiguration.h"
#include <QSettings>

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
    connect (ui->pushButtonClose,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect (ui->pushButtonSave,SIGNAL(clicked(bool)),this,SLOT(Save()));
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

void DialogConfiguration::Save()
{
    QSettings s;
    s.setValue("BlackSquareColor",ui->pushButtonBlackSquareColor->getColor());
    s.setValue("WhiteSquareColor",ui->pushButtonWhiteSquareColor->getColor());
    emit sendColors(ui->pushButtonWhiteSquareColor->getColor(),ui->pushButtonBlackSquareColor->getColor());
}
