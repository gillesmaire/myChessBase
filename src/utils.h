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
    /// \brief QString2View convert string_view to QString
    /// \param qstr
    /// \return 
    ///
    static std::string_view QString2View(const QString &qstr);
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
    ///
    /// \brief getFontFamily get the FontFamily QString from a fontName String
    /// \param fontname
    /// \return 
    ///
    static QString getFontFamily(QString fontname);
    ///
    /// \brief RecordChessFonts fill the extern QMap<QString,QMap<QString,QChar>> Pieces;
    /// ie give the correspondance for each piece in each family between Piece name and character
    /// used for the piece
    ///
    static void RecordChessFonts();
    
    ///
    /// \brief NumberSanMoves transfrorm an SAN list like e4 e5 Nf3 Nc6 to 1.e4 e5 2.Nf3 Nc6
    /// \param list list of move 
    /// \return  the list with numbers
    ///
    static QString NumberSanMoves( QStringList list);
    
    static std::u16string StringViewToUtf16(const std::string_view &str_view);

    ///
    /// \brief ECONumber return the number of ECO in the tabel ECO
    /// \return 
    ///
    static int ECONumber();
    ////
    /// \brief ListFavouriteOpening contruct a QStringList with the list
    /// of favourite openings for the user. Le file is stored in ini file of user.
    /// \return the list of vavourite
    ///
    static QStringList ListFavouriteOpenings();
    ///
    /// \brief SaveFouvouriteOpenings save the list. 
    /// \param list
    ///
    bool  SaveFouvouriteOpenings (QStringList list);
    ////
    /// \brief getUserSettingsDirectory get the name of ini directory
    /// \return 
    ///
    static QString getUserSettingsDirectory();
};
    

#endif // UTILS_H
