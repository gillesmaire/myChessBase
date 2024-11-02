#ifndef UTILS_H
#define UTILS_H

#include <QMap>
#include <QVariant>
#include <QSqlDatabase>
class Utils
{
public:
    static QMap<QString,QChar> ListPGNRecords();
    static QSqlDatabase PrepareDataBase( QString &filename);
};

#endif // UTILS_H
