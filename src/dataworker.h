#ifndef DATAWORKER_H
#define DATAWORKER_H

#include <QObject>
#include <QSqlDatabase>
#include <QString>


class DataWorker : public QObject
{
    Q_OBJECT
public:
    explicit DataWorker(QString filename,QSqlDatabase *db);
    void InsertData();
    ~DataWorker();
    
private:
    QSqlDatabase *mDb;
    QString mFileName;
signals:
    void insertionDone();
   
}; 

#endif // DATAWORKER_H
