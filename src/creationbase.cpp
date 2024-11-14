#include "creationbase.h"
#include <QSettings>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDir>
#include <fstream>


#include "ecotablegeneration.h"


CreationBase::CreationBase() {

    mFilename=Utils::getFileNameDataBase();
    QFileInfo fibase(mFilename);
    QSqlDatabase mDb=QSqlDatabase::addDatabase("QSQLITE");
    if ( ! fibase.exists() || fibase.size()==0) {
        mDb.setDatabaseName(mFilename);
        mDb.open();
        QString q;
        QMap<QString,QChar> list=Utils::ListPGNRecords();
        for (auto key:  list.keys() ){
            
            QString type=(list[key]=='T')?"TEXT":"INTEGER";
            q+=QString("'%1' %2").arg(key,type)+",";
        }
        
        QString qs1("CREATE TABLE 'Games' ('Id' INTEGER NOT NULL UNIQUE,MOVES NOT NULL,ECOPLUS,VARIANT,"
                    + q + 
                	"PRIMARY KEY('Id' AUTOINCREMENT))");
        QSqlQuery qsq1(qs1);
        qsq1.exec();
        
        QString q2 ("CREATE TABLE 'ECO' ( eco not NULL,opening NOT NULL,variation,ecoplus,pb NOT NULL,moves NOT NULL,nbm INTEGER no NULL) ");
        QSqlQuery query(q2) ;
        query.exec(); 
        QString tmpfile=QDir::temp().absolutePath();
        QString ecofile=tmpfile+QString("/eco.pgn");
        QFile::copy(":/System/eco.pgn",ecofile);
        QFile fileeco(ecofile);
         fileeco.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);
        auto file_stream=std::ifstream(ecofile.toLatin1());
        auto vis =std::make_unique<EcoTableGeneration>();
 
        mDb.transaction();
        vis->setSqlHandler(&mDb);
        chess::pgn::StreamParser parser(file_stream);
        parser.readGames(*vis);
        QFile::remove(ecofile);
        mDb.commit(); 
        
    }
    else
    {
        mDb.setDatabaseName(mFilename);
        mDb.open();
    }
 }

QSqlDatabase *CreationBase::getConnection()
{
    return &mDb;
}
