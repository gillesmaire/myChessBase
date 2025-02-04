#include "mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDir>
#include <QSettings>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QSqlQuery>
#include <QMessageBox>
#include <QtConcurrent>
#include <QSqlError>
#include <QFontDatabase>
#include <QLineEdit>
#include <QMessageBox>

#include <QMessageBox>
#include <QDir>
#include <QRegularExpression>

#include <formcounterpage.h>
#include <formboardpage.h>  


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QSettings s;
    ui->setupUi(this);
    ui->tabWidgetUnivers->setCurrentIndex(s.value("DefaultUnivers").toInt());
    connect(ui->tabWidgetUnivers,SIGNAL(currentChanged(int)),this,SLOT(SaveDefaultUnivers(int)));
    connect (ui->actionE_xit,&QAction::triggered,this,&MainWindow::close);       
 }   


void MainWindow::SaveDefaultUnivers( int i )
{   
    QSettings s;
    s.setValue("DefaultUnivers",i);
}


MainWindow::~MainWindow()
{
    delete ui;
}







