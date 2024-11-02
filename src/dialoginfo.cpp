#include "dialoginfo.h"
#include "ui_dialoginfo.h"
#include <QSettings>
#include <QRegularExpression>
#include <QFileInfo>
#include <QSqlQuery>
#include <QDebug>

DialogInfo::DialogInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogInfo)
{
    ui->setupUi(this);
    QSettings s;
    ui->lineEditFirstUse->setText(s.value("InitDate").toString());
    QString baseName=s.fileName().replace(QRegularExpression("\\.ini$"),".db");
    ui->lineEditDatabaseLocation->setText(baseName);
    QFileInfo fi(baseName);
    ui->lineEditSizeOfDatabase->setText(QString("%1").arg(fi.size()));
    QSqlQuery query("select count (*)  from  Games");
    query.next();
    ui->lineEditNumberOfGame->setText(query.value(0).toString());
    connect (ui->pushButtonClose,&QPushButton::clicked,this,&DialogInfo::close);
}

DialogInfo::~DialogInfo()
{
    delete ui;
}

