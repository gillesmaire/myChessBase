#ifndef MYVISITOR_H
#define MYVISITOR_H
#include "chess.hpp"
#include <QString>
#include <QStringList>
#include <QMap>
#include <QPair>
#include <qsqlquery.h>
#include "mainwindow.h"

using namespace chess;

///
/// \brief The MyVisitor class is derivated from pgn::Visitor from C++ Chess Library
///
class MyVisitor :  public pgn::Visitor 
{
     friend class DialogCount;
     

private:
      // contains the key values of records used in database 
      QList<QPair<QString,QVariant>> mValues;
 
      // mRecords contains all the records of database in the first place and type 'TEXT' ou 'INTEGER'
      QMap<QString,QChar>mRecords;
      
      // all moves of a game
      QStringList mMoves;

      ///
      /// \brief view2QString this function convert string_view in QString
      /// \param vue
      /// \return 
      ///
      QString view2QString(std::string_view vue )
      {
        return QString::fromUtf8(vue.data(), static_cast<int>(vue.size()));
      }
      
          ///
    ////// \brief InitValues initialize mValues with all the keys set with 0 for integer or  "" for string
    ///
     void InitValues();
     ///
     /// \brief mLastInsertId to get the Id for last insert Query to report in table 
     ///
        
    DialogProgressBarImport *mProgressBarImport;
    QSqlDatabase mDb ;
    
    
public:
    MyVisitor();
    virtual ~MyVisitor();
    ///
    /// \brief header : called  for each header tag 
    /// \param key
    /// \param value
    ///
    void header(std::string_view key, std::string_view value) ;
    ///
    /// \brief move : called for each move in the game
    /// \param move : the move in  string
    /// \param comment : additionnal comment 
    ///
    void move(std::string_view move, std::string_view comment) ;
    ///
    /// \brief startPgn : called at the start of each PNG game
    ///
    void startPgn();
    ///
    /// \brief startMoves : called before the moves of game are processed
    ///
    void startMoves();
    ///
    /// \brief endPgn : called at the end of each PGN game
    ///
    void endPgn();
    
   void IncrementCounter();
   void setConnection(QSqlDatabase *newConnection);
   void InitPtrMainWindow( MainWindow *ptr);
   void setProgressBar(DialogProgressBarImport *progressbar);
//   void StopChrono();

};

#endif // MYVISITOR_H
