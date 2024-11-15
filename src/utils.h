#ifndef UTILS_H
#define UTILS_H

#include <QMap>
#include <QVariant>
#include <QSqlDatabase>
#include <string_view>
#include "chess.hpp"

class Utils

{
public:
    static QMap<QString, QChar> ListPGNRecords();
    static QString getFileNameDataBase();
    static QString view2QString(std::string_view vue );
    static std::string toHexString(const std::array<std::uint8_t, 24>& data);
    static QByteArray PackeBoard2ByteArray(const chess::PackedBoard &arr);
    static chess::PackedBoard ByteArray2PackedBoard(const QByteArray &blob);
    static void InitializePackedBoards();
    
}; 


#endif // UTILS_H
