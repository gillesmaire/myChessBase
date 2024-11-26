#include "utils.h"
#include <QString>
#include <QSettings>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QDir>
#include <QFontDatabase>
#include <ecotablegeneration.h>

#include <chess.hpp>

extern QMap<QString,chess::PackedBoard> PackedBoards;

void Utils::RecordChessFonts()
{
    QMap<QString,QChar>P;
    extern QMap<QString,QMap<QString,QChar>> Pieces;
    P["WHITEPAWN"]='o';
    P["WHITEKNIGHT"]='m';
    P["WHITEBISHOP"]='v';
    P["WHITEROOK"]='t';
    P["WHITEQUEEN"]='w';
    P["WHITEKING"]='l';
    P["BLACKPAWN"]='o';
    P["BLACKKNIGHT"]='m';
    P["BLACKBISHOP"]='v';
    P["BLACKROOK"]='t';
    P["BLACKQUEEN"]='w';
    P["BLACKKING"]='l';
    P["NOPIECE"]=' ';
    Pieces["Magnetic"]=P;
    P.clear();

    P["WHITEPAWN"]='o';
    P["WHITEKNIGHT"]='m';
    P["WHITEBISHOP"]='v';
    P["WHITEROOK"]='t';
    P["WHITEQUEEN"]='w';
    P["WHITEKING"]='l';
    P["BLACKPAWN"]='o';
    P["BLACKKNIGHT"]='m';
    P["BLACKBISHOP"]='v';
    P["BLACKROOK"]='t';
    P["BLACKQUEEN"]='w';
    P["BLACKKING"]='l';
    P["NOPIECE"]=' ';
    Pieces["Leipzig"]=P;
    P.clear();
    
    P["WHITEPAWN"]='o';
    P["WHITEKNIGHT"]='m';
    P["WHITEBISHOP"]='v';
    P["WHITEROOK"]='t';
    P["WHITEQUEEN"]='w';
    P["WHITEKING"]='l';
    P["BLACKPAWN"]='o';
    P["BLACKKNIGHT"]='m';
    P["BLACKBISHOP"]='v';
    P["BLACKROOK"]='t';
    P["BLACKQUEEN"]='w';
    P["BLACKKING"]='l';
    P["NOPIECE"]=' ';
    Pieces["Cases"]=P;
    P.clear();
    
    P["WHITEPAWN"]='o';
    P["WHITEKNIGHT"]='m';
    P["WHITEBISHOP"]='v';
    P["WHITEROOK"]='t';
    P["WHITEQUEEN"]='w';
    P["WHITEKING"]='l';
    P["BLACKPAWN"]='o';
    P["BLACKKNIGHT"]='m';
    P["BLACKBISHOP"]='v';
    P["BLACKROOK"]='t';
    P["BLACKQUEEN"]='w';
    P["BLACKKING"]='l';
    P["NOPIECE"]=' ';
    Pieces["Maya"]=P;
    P.clear();
    
    P["WHITEPAWN"]='o';
    P["WHITEKNIGHT"]='m';
    P["WHITEBISHOP"]='v';
    P["WHITEROOK"]='t';
    P["WHITEQUEEN"]='w';
    P["WHITEKING"]='l';
    P["BLACKPAWN"]='o';
    P["BLACKKNIGHT"]='m';
    P["BLACKBISHOP"]='v';
    P["BLACKROOK"]='t';
    P["BLACKQUEEN"]='w';
    P["BLACKKING"]='l';
    P["NOPIECE"]=' ';
    Pieces["Chess-7"]=P;
    P.clear();

    P["WHITEPAWN"]='o';
    P["WHITEKNIGHT"]='m';
    P["WHITEBISHOP"]='v';
    P["WHITEROOK"]='t';
    P["WHITEQUEEN"]='w';
    P["WHITEKING"]='l';
    P["BLACKPAWN"]='o';
    P["BLACKKNIGHT"]='m';
    P["BLACKBISHOP"]='v';
    P["BLACKROOK"]='t';
    P["BLACKQUEEN"]='w';
    P["BLACKKING"]='l';
    P["NOPIECE"]=' ';
    Pieces["Marroquin"]=P;
    P.clear();

    P["WHITEPAWN"]='o';
    P["WHITEKNIGHT"]='j';
    P["WHITEBISHOP"]='n';
    P["WHITEROOK"]='t';
    P["WHITEQUEEN"]='w';
    P["WHITEKING"]='l';
    P["BLACKPAWN"]='o';
    P["BLACKKNIGHT"]='j';
    P["BLACKBISHOP"]='n';
    P["BLACKROOK"]='t';
    P["BLACKQUEEN"]='w';
    P["BLACKKING"]='l';
    P["NOPIECE"]=' ';
    Pieces["Alpha"]=P;
    P.clear();

    P["WHITEPAWN"]='o';
    P["WHITEKNIGHT"]='j';
    P["WHITEBISHOP"]='n';
    P["WHITEROOK"]='t';
    P["WHITEQUEEN"]='w';
    P["WHITEKING"]='l';
    P["BLACKPAWN"]='o';
    P["BLACKKNIGHT"]='j';
    P["BLACKBISHOP"]='n';
    P["BLACKROOK"]='t';
    P["BLACKQUEEN"]='w';
    P["BLACKKING"]='l';
    P["NOPIECE"]=' ';
    Pieces["Cheq"]=P;
    P.clear();
    
    P["WHITEPAWN"]='O';
    P["WHITEKNIGHT"]='M';
    P["WHITEBISHOP"]='V';
    P["WHITEROOK"]='T';
    P["WHITEQUEEN"]='W';
    P["WHITEKING"]='L';
    P["BLACKPAWN"]='O';
    P["BLACKKNIGHT"]='M';
    P["BLACKBISHOP"]='V';
    P["BLACKROOK"]='T';
    P["BLACKQUEEN"]='W';
    P["BLACKKING"]='L';
    P["NOPIECE"]=' ';
    Pieces["OpenChessFont"]=P;
}

QString Utils::NumberSanMoves(QStringList list)
{
 QString result;
 QString white;
 QString black;
 int i=0;
 QString  first("");
 for (auto move: list)
    {
     i++;
    if ( i%2==1 ){
      white=QString("%1%2. %3").arg(first).arg(i).arg(move) ;
      first= " ";
      }
    else {
      black=move;
      result+=white + " " + black ;
      white="";
     }
    }
  if ( ! white.isEmpty()) 
     result= result+ white;
  return (result);
}


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
std::u16string Utils::StringViewToUtf16(const std::string_view& str_view) {
    if (str_view.empty()) {
        return std::u16string();
    }
}
QString Utils::view2QString(std::string_view vue)
{
    return QString::fromUtf8(vue.data(), static_cast<int>(vue.size()));
}
std::string_view Utils::QString2View(const QString& qstr) {
    return std::string_view(reinterpret_cast<const char*>(qstr.utf16()), qstr.length() * 2);
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

QByteArray Utils::PackeBoard2ByteArray(const chess::PackedBoard& arr) {
    return QByteArray(reinterpret_cast<const char*>(arr.data()), arr.size());
}


chess::PackedBoard Utils::ByteArray2PackedBoard(const QByteArray& blob) {
    chess::PackedBoard arr{};
    std::memcpy(arr.data(), blob.data(), std::min(static_cast<size_t>(blob.size()), arr.size()));
    return arr;
}

void Utils::InitializePackedBoards()
{
    QSqlQuery query("SELECT eco, ecoplus, pb FROM ECO");
    while ( query.next()){ 
       QString ecoplus=QString("%1%2").arg(query.value("eco").toString()).arg(query.value("ecoplus").toString());
       PackedBoards[ecoplus]=Utils::ByteArray2PackedBoard(query.value("pb").toByteArray());
    }
      
}

QString Utils::getFontFamily(QString fontname)
{
  extern QMap <QString,int> fontList;
  int i =fontList[fontname];
  QString family;
  if (QFontDatabase::applicationFontFamilies(i).size()!=0)
        return QFontDatabase::applicationFontFamilies(i).at(0);
 return QString();
}


int Utils::ECONumber()
{
    QSqlQuery query("select count (*)  from  ECO");
    query.next();
    return query.value(0).toInt();
}

QStringList Utils:: ListFavouriteOpenings()
{
    QFile file(getUserSettingsDirectory()+"/openings.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return {};
    }
    QStringList selectedOpenings;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed(); // Lire et nettoyer chaque ligne
        if (!line.isEmpty() && !line.startsWith('#')) { // Ignorer les commentaires
            selectedOpenings.append(line);
        }
    }
    file.close();
    return selectedOpenings;
}

bool Utils::SaveFouvouriteOpenings(QStringList list)
{
     QFile file(getUserSettingsDirectory()+"/openings.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false; 
     }
    QTextStream out(&file);
    for (const QString& code : list) {
        out << code << "\n";
        }
    file.close();
    return true;
}


QString Utils::getUserSettingsDirectory() {
    QSettings settings;
    QFileInfo fileInfo(settings.fileName());
    return fileInfo.absolutePath();
}
