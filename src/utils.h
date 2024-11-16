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
    ///
    /// \brief ListPGNRecords this function describe the records from PNG file who will
    /// be used in database. The other ones will not be include in the table ECO from database. The type 
    /// is T for Text, I for integer. The PB (packet bit) the Name of opening, the name of variant are not included here.
    /// \return 
    ///
    static QMap<QString, QChar> ListPGNRecords();
    ///
    /// \brief getFileNameDataBase calculate the DataBase Name ie /home/user/.config/myChessBase.db
    /// \return 
    ///
    static QString getFileNameDataBase();
    ///
    /// \brief view2QString convert std::view to QString
    /// \param vue
    /// \return 
    ///
    static QString view2QString(std::string_view vue );
    ///
    /// \brief toHexString  convert a PacketBoard to QString
    /// \param data
    /// \return 
    ///
    static std::string toHexString(const std::array<std::uint8_t, 24>& data);
    ///
    /// \brief PackeBoard2ByteArray convert a packed Board tp QByteArray
    /// \param arr
    /// \return 
    ///
    static QByteArray PackeBoard2ByteArray(const chess::PackedBoard &arr);
    ///
    /// \brief ByteArray2PackedBoard convert a QByteArray to PackedBoard
    /// \param blob
    /// \return 
    ///
    static chess::PackedBoard ByteArray2PackedBoard(const QByteArray &blob);
    ///
    /// \brief InitializePackedBoards to be modified ... waiting
    ///
    static void InitializePackedBoards();
    
}; 


#endif // UTILS_H
