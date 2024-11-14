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
    QString rec=recs.join(',');
    QString val=vals.join(',');
 
    QString req=QString("INSERT INTO Games (%1) VALUES (%2)").arg(rec).arg(val);
    QSqlQuery query(req,mDb);
    IncrementCounter();
   
}

void MyVisitor::IncrementCounter()
{
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


void MyVisitor::setConnection(QSqlDatabase *newConnection)
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

