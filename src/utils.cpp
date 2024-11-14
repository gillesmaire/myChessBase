#include "utils.h"
#include <QString>
#include <QSettings>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QDir>
#include <ecotablegeneration.h>

#include <chess.hpp>





QMap<QString, QChar> Utils::ListPGNRecords()
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

QString Utils::getFileNameDataBase()
{
    QSettings s;
    QString configfile= s.fileName();
    QFileInfo fi(configfile);
    return (fi.absolutePath()+"/myChessBase.db");
}

QString Utils::view2QString(std::string_view vue)
{
    return QString::fromUtf8(vue.data(), static_cast<int>(vue.size()));
}

std::string Utils::toHexString(const std::array<uint8_t, 24> &data) {
    std::ostringstream oss;
    oss << "x'";  // Préfixe pour indiquer un BLOB en hexadécimal dans SQLite
    for (auto byte : data) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    oss << "'";
   return oss.str();
}
