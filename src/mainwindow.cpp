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
#include "chess.hpp"
#include <QMessageBox>

#include <memory>
#include <fstream>

#include "myvisitor.h"
#include "ecotablegeneration.h"
#include "dialoginfo.h"
#include "dialogabout.h"
#include <formcounterpage.h>
#include <formboardpage.h>  
#include <formmainwidget.h>
#include "dialogprogressbarimport.h"
#include "dialogconfiguration.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect (ui->actionE_xit,&QAction::triggered,this,&QMainWindow::close);                     // Llose this windows
    connect (ui->actionLoad_Pgn_file,&QAction::triggered,this,&MainWindow::LoadPGNFile);        // Load PGN files into data base
    connect (ui->actionInformations,&QAction::triggered,this,&MainWindow::ShowInformations);    // Show information dialog
    connect (ui->actionAbout,&QAction::triggered,this,&MainWindow::About);                      // Show about dialog
    connect (ui->actionRemove_Database,&QAction::triggered,this,&MainWindow::RemoveDatabase);   // Flush the database's tables
    connect (ui->actionConfiguration,&QAction::triggered,this,&MainWindow::Configuration) ; 
    connect (ui->actionFlip,&QAction::triggered,this,&MainWindow::FlipBoard);
    connect (ui->actionShow_Fen,&QAction::triggered,this,&MainWindow::ShowFen);
    connect (ui->actionReadEcoPGN,&QAction::triggered, this,&MainWindow::MakeECOTable);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setDataBaseConnector(QSqlDatabase *connection)
{
    mConnection=connection;
}

void MainWindow::setDataBaseName(QString file)
{
    mDataBaseFile=file;
}

void MainWindow::IncrementCounter()
{
    
}

void MainWindow::FlipBoard()
{
    mFlipBoard=!mFlipBoard;
    ui->chessBoard->flipBoard(mFlipBoard);
}

void MainWindow::RemoveDatabase()
{
 
    QMessageBox msgBox;
    msgBox.setText("Dangerous operation");
    msgBox.setInformativeText("Do you really want to delete all you database to create an other one ?");
    msgBox.setStandardButtons( QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();
    if (ret==QMessageBox::Yes) 
    {
      QString req=QString("DELETE FROM Games");
      QSqlQuery query(req);
      query.exec();
    }
}

void MainWindow::LoadPGNFile()
{
     QSettings s;
     QString dir=s.value("DataBaseDir",QDir::homePath()).toString();
     QString filename=QFileDialog::getOpenFileName(this,tr("Select a PGN file to include in Database"),dir,tr("PGN file (*.pgn)"));
     QFileInfo fi(filename);
     s.setValue("DataBaseDir",fi.dir().absolutePath());
     s.sync();   
    
    if  (filename.isEmpty() ) return;
    mProgressBar=new DialogProgressBarImport(this);
    QSqlDatabase *db=mConnection;
    DialogProgressBarImport *pb=mProgressBar;
    db->transaction();
    QObject::connect(&mWatcher, &QFutureWatcher<void>::finished, this, [db,pb]() {
       if  (! db->commit())
         {
        qDebug()<<db->lastError();
        } 
        else 
       {
        pb->ClockStop(); 
       }
    });
    QFuture<void> future=QtConcurrent::run(LoadPGNFileConcurrent,filename,mConnection,mProgressBar);
    mWatcher.setFuture(future);
    mProgressBar->exec();
    delete(mProgressBar);
    mWatcher.disconnect();
    
}


void MainWindow::LoadPGNFileConcurrent(QString filename, QSqlDatabase *connection ,DialogProgressBarImport *progressbar)
{
   
    auto file_stream=std::ifstream(filename.toLatin1());
    auto vis =std::make_unique<MyVisitor>();
    vis->setConnection(connection);
    vis->setProgressBar(progressbar);
    //if ( !connection->transaction()) qDebug("Connection problem !");
    pgn::StreamParser parser(file_stream);
    try {
        parser.readGames(*vis);
    } 
    catch (const chess::pgn::StreamParserException& e){
     std::cerr << "Erreur lors de l'analyse du fichier : " << e.what() << "\n";
     }
    catch (...) {
     std::cerr << "Other error: " << "\n";
    }
   
  
}

void MainWindow::ModifyColor(QColor whitesquarecolor, QColor blacksquarecolor)
{
    ui->chessBoard->setBlackSquareColor(blacksquarecolor);
    ui->chessBoard->setWhiteSquareColor(whitesquarecolor);
    ui->chessBoard->update();
}

void MainWindow::Configuration()
{
  DialogConfiguration c(this);
  connect ( &c, SIGNAL(SendColors(QColor,QColor)),this,SLOT(ModifyColor(QColor,QColor)));
  c.exec();
}

/// show informations as : number of games in the database, version of this sotware, size of database
void MainWindow::ShowInformations()
{
    DialogInfo di(this);
    di.exec();
}

void MainWindow::About()
{
    DialogAbout da(this);
    da.exec();
}


void MainWindow::ShowFen(bool ok)
{
    if ( ok && ! mFENShown )  {
       mFENShown=true;
       mFEN=new QLineEdit(getFen());
       ui->statusbar->addWidget(mFEN);
     }
   else if (!ok && mFENShown )
   { 
    mFENShown=false;
    ui->statusbar->removeWidget(mFEN);
   }
    
}

QString MainWindow::getFen()
{
    return QString(ui->chessBoard->getFEN());
}


////
/// \brief MainWindow::MakeECOTable Generate an ECO Table. It is made by adminsitrator
///  The Table is generated from David Barnes file

void MainWindow::MakeECOTable()
{
  QString EcoFile=QFileDialog::getOpenFileName(this,tr("Open the David Barnes File to generate the ECO table"));
  auto file_stream=std::ifstream(EcoFile.toLatin1());
  auto vis =std::make_unique<EcoTableGeneration>();
  pgn::StreamParser parser(file_stream);
  parser.readGames(*vis);
}

