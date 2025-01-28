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

#include <memory>
#include <fstream>
#include "chess.hpp"

#include "readpgn.h"
#include <formcounterpage.h>
#include <formboardpage.h>  
#include "dialogprogressbarimport.h"
#include "dialogshortcuts.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidgetButtonVsInfo->setCurrentIndex(0);
    QSettings s;
    ui->chessBoard->setNumberCase(s.value("ShowCaseNumbers").toBool());
    ui->actionShow_cases_number->setChecked(s.value("ShowCaseNumbers").toBool());
    connect (ui->actionE_xit,&QAction::triggered,this,&MainWindow::close);                     // Llose this windows
    connect (ui->actionLoad_Pgn_file,&QAction::triggered,this,&MainWindow::LoadPGNFile);        // Load PGN files into data base
    connect (ui->actionMy_Preferences,&QAction::triggered,this,&MainWindow::MyPreferences);
    connect (ui->actionRemove_Database,&QAction::triggered,this,&MainWindow::SuppressDataBaseGames);   // Flush the database's tables
    connect (ui->actionSupprimer_le_fichier_DataBase,&QAction::triggered,this,&MainWindow::SuppressDataBase); 
    connect (ui->actionFlip,&QAction::triggered,this,&MainWindow::FlipBoard);
    connect (ui->actionShow_Fen,&QAction::triggered,this,&MainWindow::ShowFen);
    connect (ui->actionShorcuts,&QAction::triggered,this,&MainWindow::ShoShortCuts);
    connect (ui->actionShow_cases_number,&QAction::triggered,this,&MainWindow::SaveCaseNumbers);
    connect (ui->actionCreate_a_Pgn_file,&QAction::triggered,this,&MainWindow::ActiveWidget);
    connect (ui->pushButtonStart,&QPushButton::clicked,this,&MainWindow::goStart);
    connect (ui->pushButtonEnd,&QPushButton::clicked,ui->chessBoard,&ChessBoard::goEnd);
    connect (ui->pushButtonNext,&QPushButton::clicked,ui->chessBoard,&ChessBoard::goNext);
    connect (ui->pushButtonBack,&QPushButton::clicked,ui->chessBoard,&ChessBoard::goBack);
    connect (ui->chessBoard,SIGNAL(MovesModified(QStringList)),ui->CreationPGN,SLOT(GetListMoves(QStringList)));
    connect (ui->PreferenceUnivers,SIGNAL(Informations(QString,QString,QString,QString,QString)),
            this,SLOT(ShowVariation(QString,QString,QString,QString,QString)));
    connect (ui->pgnEditor,SIGNAL(showFen()),this,SLOT(ShowFen()));
           
    
}   


void MainWindow::goStart()
{
  ui->chessBoard->goStart();
  ui->CreationPGN->SetListMove(QString());
}

void MainWindow::goBack()
{
    ui->chessBoard->goBack();
    QString listofmoves=ui->CreationPGN->getListMove();
    listofmoves.replace (QRegularExpression("\\d+\\."),"");
    QStringList l=listofmoves.split(" ");
    l.removeLast();
    ui->CreationPGN->SetListMove(l.join(" "));
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

void MainWindow::MyPreferences()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::FlipBoard()
{
    mFlipBoard=!mFlipBoard;
    ui->chessBoard->flipBoard(mFlipBoard);
    
}

void MainWindow::SuppressDataBaseGames()
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

void MainWindow::SuppressDataBase()
{
   QSettings s;
   QFileInfo fi(s.fileName());
   QString filename=fi.absolutePath()+"/myChessBase.db";
   QFile F(filename);
   qDebug()<<filename;
   F.remove();
   
   
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
   
    auto file_stream=std::ifstream(filename.toLatin1());
    auto vis =std::make_unique<ReadPGN>();
    vis->setConnection(mConnection);
    pgn::StreamParser parser(file_stream);
    
    
    
    mProgressBar=new DialogProgressBarImport(this);
    mProgressBar->show();
    vis->setProgressBar(mProgressBar);
    qDebug()<<"debut transaction"<<mConnection->transaction();
    
    try {
        parser.readGames(*vis);
    } 
    catch (const chess::pgn::StreamParserException& e){
     std::cerr << "Erreur lors de l'analyse du fichier : " << e.what() << "\n";
     }
    catch (...) {
     std::cerr << "Other error: " << "\n";
     
    }
    qDebug()<<"fin transaction"<<mConnection->commit();
    
    
}


void MainWindow::Update()
{
    update();
    ui->chessBoard->AskUpdate();
    
}






void MainWindow::ShowFen()
{
   if ( ! mFENShown )  {
       mFENShown=true;
       mFEN=new QLineEdit(getFen());
       ui->statusbar->addWidget(mFEN);
     }
   else 
   { 
    mFENShown=false;
    ui->statusbar->removeWidget(mFEN);
   }
    
}

void MainWindow::ShoShortCuts()
{
   DialogShortCuts dsc(this);
   dsc.exec();
}

QString MainWindow::getFen()
{
    return QString(ui->chessBoard->getFEN());
}



void MainWindow::SaveCaseNumbers()
{
        QSettings s;
        s.setValue("ShowCaseNumbers",ui->actionShow_cases_number->isChecked() );
        ui->chessBoard->setNumberCase(ui->actionShow_cases_number->isChecked());
}

////
/// \brief MainWindow::MakeECOTable Generate an ECO Table. It is made by adminsitrator
///  The Table is generated from David Barnes file


void MainWindow::ActiveWidget()
{
   if ( this->sender()->objectName()==QString("actionCreate_a_Pgn_file")) 
     ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::ShowVariation(QString ECO,QString opening,QString variation,QString ecoplus,QString moves)
{
    ui->stackedWidgetButtonVsInfo->setCurrentIndex(1);
    ui->pageInfo->setTitle(QString("ECO  %1 (%4) :  %2 - %3 ").arg(ECO).arg(opening).arg(variation).arg(ecoplus));
    ui->chessBoard->PlayListOfSANMove(moves.split(' '));
}
