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
    static QString view2QString(std::string_view vue )
      {
        return QString::fromUtf8(vue.data(), static_cast<int>(vue.size()));
      }
};

#endif // UTILS_H
