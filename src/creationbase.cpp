#include "creationbase.h"
#include <QSettings>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDir>
#include <QSqlError>

#include <fstream>
#include "utils.h"


#include "ecotablegeneration.h"



CreationBase::CreationBase() {

    mFilename=Utils::getFileNameDataBase();
    QFileInfo fibase(mFilename);
    mDb=QSqlDatabase::addDatabase("QSQLITE");
    
   
    if ( ! fibase.exists() || fibase.size()==0) {
        mDb.setDatabaseName(mFilename);
        mDb.open();
        CreateECOTable();
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

void CreationBase::CreateECOTable()
{
    QString q ("CREATE TABLE 'ECO' ( eco not NULL,ecoplus,opening NOT NULL,variation,moves NOT NULL,pb BLOB,  nbm INTEGER NOT NULL, wins INTEGER , losts INTEGER , equals INTEGER ) ");
    QSqlQuery query(q) ;
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
