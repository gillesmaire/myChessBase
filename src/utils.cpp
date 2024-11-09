#include "utils.h"
#include <QString>
#include <QSettings>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlQuery>

QMap <QString,QChar> Utils::ListPGNRecords()
{
    QMap<QString,QChar>  list;
    
    list["Black"]='T';
    list["BlackElo"]='I';
    list["BlackFideId"]='I';
    list["BlackTitle"]='T';
    list["Date"]='T';
    list["ECO"]='T';
    list["Event"]='T';
    list["Result"]='T';
    list["Round"]='T';
    list["Site"]='T';
    list["White"]='T';
    list["WhiteElo"]='I';
    list["WhiteFideId"]='I';
    list["WhiteTitle"]='T';
    return (list);
}

 QSqlDatabase Utils::PrepareDataBase(QString &filename)
{
    QSettings s;
    QString configfile= s.fileName();
    QFileInfo fi(configfile);
    filename=fi.absolutePath()+"/myChessBase.db";
    QFileInfo fibase(filename);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    if ( ! fibase.exists() || fibase.size()==0) {
        db.setDatabaseName(filename);
        db.open();
        QString q;
        QMap<QString,QChar> list=Utils::ListPGNRecords();
        for (auto key:  list.keys() ){
            
            QString type=(list[key]=='T')?"TEXT":"INTEGER";
            q+=QString("'%1' %2").arg(key,type)+",";
        }
        
        QString qs1("CREATE TABLE 'Games' ('Id' INTEGER NOT NULL UNIQUE,MOVES NOT NULL,ECOPLUS,VARIANT"
                    + q + 
                	"PRIMARY KEY('Id' AUTOINCREMENT))");
        QSqlQuery qsq1(qs1);
        qsq1.exec();
        QString qs2("CREATE TABLE 'ECOPLUS' ('Id' INTEGER NOT NULL UNIQUE,MOVES NOT NULL,ECOPLUS,VARIANT"
                    + q + 
                	"PRIMARY KEY('Id' AUTOINCREMENT))");
        
    }
    else
    {
        db.setDatabaseName(filename);
        db.open();
    }
    return (db) ;
}
