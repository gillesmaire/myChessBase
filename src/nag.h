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
#ifndef NAG_H
#define NAG_H

#include <QString>
#include <QStringList>
#include <QObject>
#include <QTextEdit>

///
/// \brief descriptions this tab contains the list of NAGS in english ready 
/// to be translated
///
static QStringList NagDescriptions ={
 
QObject::tr("null annotation"),
QObject::tr("good move (!)"),
QObject::tr("poor move (?)"),
QObject::tr("very good move (!!)"),
QObject::tr("very poor move (??)"),
QObject::tr("speculative move (!?)"),
QObject::tr("questionable move (?!)"),
QObject::tr("forced move (all others lose quickly)"),
QObject::tr("singular move (no reasonable alternatives)"),
QObject::tr("worst move"),
QObject::tr("drawish position"),
QObject::tr("equal chances, quiet position"),
QObject::tr("equal chances, active position"),
QObject::tr("unclear position"),
QObject::tr("White has a slight advantage"),
QObject::tr("Black has a slight advantage"),
QObject::tr("White has a moderate advantage"),
QObject::tr("Black has a moderate advantage"),
QObject::tr("White has a decisive advantage"),
QObject::tr("Black has a decisive advantage"),
QObject::tr("White has a crushing advantage (Black should resign)"),
QObject::tr("Black has a crushing advantage (White should resign)"),
QObject::tr("White is in zugzwang"),
QObject::tr("Black is in zugzwang"),
QObject::tr("White has a slight space advantage"),
QObject::tr("Black has a slight space advantage"),
QObject::tr("White has a moderate space advantage"),
QObject::tr("Black has a moderate space advantage"),
QObject::tr("White has a decisive space advantage"),
QObject::tr("Black has a decisive space advantage"),
QObject::tr("White has a slight time (development) advantage"),
QObject::tr("Black has a slight time (development) advantage"),
QObject::tr("White has a moderate time (development) advantage"),
QObject::tr("Black has a moderate time (development) advantage"),
QObject::tr("White has a decisive time (development) advantage"),
QObject::tr("Black has a decisive time (development) advantage"),
QObject::tr("White has the initiative"),
QObject::tr("Black has the initiative"),
QObject::tr("White has a lasting initiative"),
QObject::tr("Black has a lasting initiative"),
QObject::tr("White has the attack"),
QObject::tr("Black has the attack"),
QObject::tr("White has insufficient compensation for material deficit"),
QObject::tr("Black has insufficient compensation for material deficit"),
QObject::tr("White has sufficient compensation for material deficit"),
QObject::tr("Black has sufficient compensation for material deficit"),
QObject::tr("White has more than adequate compensation for material deficit"),
QObject::tr("Black has more than adequate compensation for material deficit"),
QObject::tr("White has a slight center control advantage"),
QObject::tr("Black has a slight center control advantage"),
QObject::tr("White has a moderate center control advantage"),
QObject::tr("Black has a moderate center control advantage"),
QObject::tr("White has a decisive center control advantage"),
QObject::tr("Black has a decisive center control advantage"),
QObject::tr("White has a slight kingside control advantage"),
QObject::tr("Black has a slight kingside control advantage"),
QObject::tr("White has a moderate kingside control advantage"),
QObject::tr("Black has a moderate kingside control advantage"),
QObject::tr("White has a decisive kingside control advantage"),
QObject::tr("Black has a decisive kingside control advantage"),
QObject::tr("White has a slight queenside control advantage"),
QObject::tr("Black has a slight queenside control advantage"),
QObject::tr("White has a moderate queenside control advantage"),
QObject::tr("Black has a moderate queenside control advantage"),
QObject::tr("White has a decisive queenside control advantage"),
QObject::tr("Black has a decisive queenside control advantage"),
QObject::tr("White has a vulnerable first rank"),
QObject::tr("Black has a vulnerable first rank"),
QObject::tr("White has a well protected first rank"),
QObject::tr("Black has a well protected first rank"),
QObject::tr("White has a poorly protected king"),
QObject::tr("Black has a poorly protected king"),
QObject::tr("White has a well protected king"),
QObject::tr("Black has a well protected king"),
QObject::tr("White has a poorly placed king"),
QObject::tr("Black has a poorly placed king"),
QObject::tr("White has a well placed king"),
QObject::tr("Black has a well placed king"),
QObject::tr("White has a very weak pawn structure"),
QObject::tr("Black has a very weak pawn structure"),
QObject::tr("White has a moderately weak pawn structure"),
QObject::tr("Black has a moderately weak pawn structure"),
QObject::tr("White has a moderately strong pawn structure"),
QObject::tr("Black has a moderately strong pawn structure"),
QObject::tr("White has a very strong pawn structure"),
QObject::tr("Black has a very strong pawn structure"),
QObject::tr("White has poor knight placement"),
QObject::tr("Black has poor knight placement"),
QObject::tr("White has good knight placement"),
QObject::tr("Black has good knight placement"),
QObject::tr("White has poor bishop placement"),
QObject::tr("Black has poor bishop placement"),
QObject::tr("White has good bishop placement"),
QObject::tr("Black has good bishop placement"),
QObject::tr("White has poor rook placement"),
QObject::tr("Black has poor rook placement"),
QObject::tr("White has good rook placement"),
QObject::tr("Black has good rook placement"),
QObject::tr("White has poor queen placement"),
QObject::tr("Black has poor queen placement"),
QObject::tr("White has good queen placement"),
QObject::tr("Black has good queen placement"),
QObject::tr("White has poor piece coordination"),
QObject::tr("Black has poor piece coordination"),
QObject::tr("White has good piece coordination"),
QObject::tr("Black has good piece coordination"),
QObject::tr("White has played the opening very poorly"),
QObject::tr("Black has played the opening very poorly"),
QObject::tr("White has played the opening poorly"),
QObject::tr("Black has played the opening poorly"),
QObject::tr("White has played the opening well"),
QObject::tr("Black has played the opening well"),
QObject::tr("White has played the opening very well"),
QObject::tr("Black has played the opening very well"),
QObject::tr("White has played the middlegame very poorly"),
QObject::tr("Black has played the middlegame very poorly"),
QObject::tr("White has played the middlegame poorly"),
QObject::tr("Black has played the middlegame poorly"),
QObject::tr("White has played the middlegame well"),
QObject::tr("Black has played the middlegame well"),
QObject::tr("White has played the middlegame very well"),
QObject::tr("Black has played the middlegame very well"),
QObject::tr("White has played the ending very poorly"),
QObject::tr("Black has played the ending very poorly"),
QObject::tr("White has played the ending poorly"),
QObject::tr("Black has played the ending poorly"),
QObject::tr("White has played the ending well"),
QObject::tr("Black has played the ending well"),
QObject::tr("White has played the ending very well"),
QObject::tr("Black has played the ending very well"),
QObject::tr("White has slight counterplay"),
QObject::tr("Black has slight counterplay"),
QObject::tr("White has moderate counterplay"),
QObject::tr("Black has moderate counterplay"),
QObject::tr("White has decisive counterplay"),
QObject::tr("Black has decisive counterplay"),
QObject::tr("White has moderate time control pressure"),
QObject::tr("Black has moderate time control pressure"),
QObject::tr("White has severe time control pressure"),
QObject::tr("Black has severe time control pressure")      
} ;

///
/// \brief The Nag class contains only one static function returning
/// the NAG translated from english
///
class Nag
{
public:
    ///
    /// \brief getNagDescription give a translated string corresponding with 
    /// the NAG number 
    /// \param nag : the NAG number
    /// \return 
    ///
    static QString getNagDescription(int nag) ;
    ///
    /// \brief getNagList 
    /// \return  return the list of NAG from 0 to last one
    ///
    static QStringList getNagList();
    ///
    /// \brief getNagListNumbered same but add "number -" before each NAG 
    /// \return 
    ///
    static QStringList getNagListNumbered();
    
    ///
    /// \brief getNag get ! ? or #10 for other nags 
    /// \param linecombobox the current combobox ie "number - text of nag"
    /// \return  for the 6 first nag return the ! !! etc or the #nn for other tags
    ///
    static QString getNag(QString linecombobox);
    
    ///
    /// \brief isNag test if caracters under the cursor of QTextEdit are nag
    /// \return 
    ///
    static bool isNag(QTextEdit *te);
    
    
    

};


#endif // NAG_H
