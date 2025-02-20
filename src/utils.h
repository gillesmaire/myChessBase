// GPL 3.0 License
// myChessBase Project
// Copyright (c) 2025 Gilles Maire <gilles@gillesmaire.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// THIS FILE IS AUTO GENERATED DO NOT CHANGE MANUALLY.
//
// Source: https://github.com/gillesmaire/myChessbase.git
//
//
// VERSION: 0.1
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
    ///
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
    
 //   static std::u16string StringViewToUtf16(const std::string_view &str_view);

    ///
    /// \brief ECONumber return the number of ECO in the label ECO
    /// \return 
    ///
    // static int ECONumber();
    ////
    /// \brief ListFavouriteOpening contruct a QStringList with the list
    /// of favourite openings for the user. Le file is stored in ini file of user.
    /// \return the list of vavourite
    ///
    //static QStringList ListFavouriteOpenings();
    ///
    /// \brief SaveFouvouriteOpenings save the list. 
    /// \param list
    ///
    //bool  SaveFouvouriteOpenings (QStringList list);
    ////
    /// \brief getUserSettingsDirectory get the name of ini directory
    /// \return 
    ///
    //static QString getUserSettingsDirectory();
    
    //static void PrintChrono();
    
    ///
    /// \brief PieceUTF8 this print knight and other figures by N B R Q K
    /// \param piece :   N B R Q K
    /// \param color :  discinct the utf8 for white an black pieces
    /// \param casePosition : the string to transform for example e4 inchanged ... Nf3 transformed
    /// \return 1. e2 e4 2. NF3 Nc6
    ///
    static QString PieceUTF8(QChar piece, chess::Color color);

    ///
    /// \brief PieceUTF8 this print knight and other figures by utf8 graphic
    /// \param piece :   N B R Q K by the utf8 fig
    /// \param color :  discinct the utf8 for white an black pieces
    /// \param casePosition : the string to transform for example e4 inchanged ... Nf3 transformed
    /// \return 
    ///
    static QString NumberSanUTF8Moves(QStringList list);
    
    
    ///
    /// \brief deduceMove for a move like e4 and the Board is the correct 
    ///        position, return the e2e4 move in QString format
    /// \param board : the board positionned in the e2e4 stt
    /// \param shortmove
    /// \return  the move if no error or the QString "error" if error
    ///
    static QString deduceMove(chess::Board  &board, QString shortmove);
    
    
     ///
    /// \brief MimeOK test if a file is a PGN 
    /// \param text
    /// \return  true if MIME has 1. e4 or 1. d5 etc...
    ///
    static bool MimeOK(QString text);
    
    ///
    /// \brief MimeNoBlankOK test if a file is a PGN 
    /// \param text
    /// \return true if MIME hase 1.e4 or 1.d5 
    ///
    static bool MimeNoBlankOK(QString text);
    
    ///
    /// \brief convertMumDotPiece2NumDotBlankPiece
    /// \param pngame
    /// \return 
    ///
    
    static QString convertMumDotPiece2NumDotBlankPiece(QString pngame);
    
 
};
#endif // UTILS_H
