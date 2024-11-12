#ifndef UTILS_H
#define UTILS_H

#include <QMap>
#include <QVariant>
#include <QSqlDatabase>
#include <string_view>
class Utils

{
public:
    static QMap<QString, QChar> ListPGNRecords();
    static QSqlDatabase PrepareDataBase( QString &filename);
    static QString view2QString(std::string_view vue );
    static std::string toHexString(const std::array<std::uint8_t, 24>& data);
};


#endif // UTILS_H
