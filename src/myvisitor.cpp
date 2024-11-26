#include "myvisitor.h"
#include <QDebug>
#include <QSqlRecord>
#include <QList>
#include <QVariant>
#include <QString>
#include <utils.h>
#include <QSettings>
#include <QFileInfo>
#include <QThread>
#include <QSqlQuery>
#include <QSqlError>

#include "dialogprogressbarimport.h"
#include <QAtomicInt>



MyVisitor::MyVisitor()
{ 
    mRecords=Utils::ListPGNRecords();
    QString connectionName = QString("ConnectionMyVis-%1").arg(reinterpret_cast<quintptr>(QThread::currentThreadId()));
    mDb = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    mDb.setDatabaseName(Utils::getFileNameDataBase());
   if (!mDb.open()) {
    qWarning() << "MyChessBase : failed to open database in thread" << QThread::currentThreadId();
      return;
    }
   else mDb.transaction();
    
}



MyVisitor::~MyVisitor()
{
     mProgressBarImport->ClockStop();
     mDb.commit();
     mDb.close();
}


///
/// \brief MyVisitor::startPgn is the first event when program start to read a PGN
/// It is also the start of reading header
///
void MyVisitor::startPgn()
{
    InitValues();
    mMoves.clear();
}

///
/// \brief MyVisitor::header this function is call when Event or other records are read (date etc)
/// \param key
/// \param value
///
void MyVisitor::header(std::string_view key, std::string_view value)
{

    QString k=view2QString(key);
    QString v=view2QString(value);
    int i=0;
    for (const auto &pair : mValues) 
    {
      if (pair.first==k) 
           {
           QPair<QString,QString> elem(k,v);
           mValues.replace(i,elem);
           break;
           }
      i++ ;
    }
}

///
/// \brief MyVisitor::move each move are given with an optional comment without black or white indication nor
/// number of move.
/// \param move
/// \param comment
///
void MyVisitor::move(std::string_view move, std::string_view )
{
    mMoves<<view2QString(move);
}


///
/// \brief MyVisitor::startMoves this function is called before the first move is done (before 1.e4 for example) It is 
/// the end of header
///
void MyVisitor::startMoves()
{
}

///
/// \brief MyVisitor::endPgn is the last
///
void MyVisitor::endPgn()
{
    QStringList recs;
    QStringList  vals;
    
    
    QString m=mMoves.join(' ');
    m="'"+m+"'";
    vals<<m;
    recs<<"MOVES";
    for ( auto info : mValues)
     {
        recs<<info.first;
        QString val;
        if ( mRecords[info.first]=='T' )
                val=QString("'%1'").arg(info.second.toString());
        else val=info.second.toString();
         vals<<val;
    }
   
    recs<<"ecoplus";
    QString plus=CalcEcoEcoPlus( mMoves, 40);
    vals<<"'"+plus+"'";
   
    QString rec=recs.join(',');
    QString val=vals.join(',');
    QString req=QString("INSERT INTO Games (%1) VALUES (%2)").arg(rec).arg(val);
    QSqlQuery query(req,mDb);
    QString q;
    QMap<QString,QChar> list=Utils::ListPGNRecords();
    for (auto key:  list.keys() ){
            QString type=(list[key]=='T')?"TEXT":"INTEGER";
            q+=QString("'%1' %2").arg(key,type)+",";
        }
    
    
    IncrementCounter();
   
    
   
}

void MyVisitor::

IncrementCounter()
{
    mProgressBarImport->CountIncrement();
}

///
/// \brief MyVisitor::InitValues on each pgn mvalues is reset with ('' or 0) if record is text or integer
///
void MyVisitor::InitValues()    
{
    mValues.clear();
    QMap<QString,QChar> map=Utils::ListPGNRecords();
    
    for (auto m : Utils::ListPGNRecords().keys())
    {
      if (map[m]=='T')
        mValues.append(QPair<QString,QVariant>(m,""));
      else if (map[m]=='I')
        mValues.append(QPair<QString,QVariant>(m,0));
      else 
        mValues.append(QPair<QString,QVariant>(m,0));
    }
    
}

QString MyVisitor::CalcEcoEcoPlus(QStringList Moves, int numberOfMovesAnalyzed)
{
  extern  QMap<QString,chess::PackedBoard> PackedBoards; 
  //BackedBoards contains all openings packed board
  QStringList results;
  
  // results contains the longuest combinaison
  QString begining;
  QStringList added;
  // from the first moves we calculate all the packed
  // // e2 e5 Cf3 Cf6 Cxe5.....
  for (auto move : Moves){
      added<<move;
      if ( added.count()>numberOfMovesAnalyzed) break;
    } // e2 e4 Cf3 ... but 20 moves ( number of Analysed moves) 
  // added contains the first moves of game we can find all the opening 
  chess::Board board(constants::STARTPOS);
  // we prepare a board from begining
  for (auto m : added) {
      std::string utf8String = m.toUtf8().toStdString();
      chess::Move move =chess::uci::parseSan(board,std::string_view(utf8String));
      // we make the move
      board.makeMove(move);
      // we calculate the packed
      auto packed=chess::Board::Compact::encode(board);
      // is the packed in know as a opening
      for (auto ecoplus: PackedBoards.keys())
          { 
           if ( PackedBoards[ecoplus]==packed )
             {
               // we know  an opening candidate we have to get eco ecoplus and nbm (number of move)
               results<<ecoplus;
             }
          }       
    }
   // results contains all the candidates we choose the longuest who is the last
   return (results.last());  
}
      
       


void MyVisitor::setConnection(QSqlDatabase *)
{
    // QSettings s;
    // QString configfile= s.fileName();
    // QFileInfo fi(configfile);
    // QString filename=fi.absolutePath()+"/myChessBase.db";
    // QFileInfo fibase(filename);
    // QSqlDatabase mDb=QSqlDatabase::addDatabase("QSQLITE");
}

void MyVisitor::setProgressBar( DialogProgressBarImport *progressbar)
{
    mProgressBarImport =progressbar;
}

