#ifndef CREATIONBASE_H
#define CREATIONBASE_H
#include <QString>
#include <QSqlDatabase>

class CreationBase
{
public:
    CreationBase();
    QSqlDatabase * getConnection();
    QString getDataBaseFileName(){ return mFilename; }
private:
    void CreateECOTable();
    QSqlDatabase mDb ;
    QString mFilename;
};

#endif // CREATIONBASE_H
