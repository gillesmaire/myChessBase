#include "ecotablegeneration.h"
#include <QSqlQuery>
#include <QSqlError>

EcoTableGeneration::EcoTableGeneration() {}


void EcoTableGeneration::startPgn() { 
   
   mRecords.clear();
   mValues.clear();
   mMoves.clear();
}

void EcoTableGeneration::header(std::string_view key, std::string_view value) {
    mRecords<<Utils::view2QString(key);
    mValues<<Utils::view2QString(value);
}

void EcoTableGeneration::move(std::string_view move, std::string_view ) {
    mMoves<< Utils::view2QString(move);
}

void EcoTableGeneration::endPgn()

{
   
     QString sqlreq=QString(
          "INSERT INTO ECO ( eco, opening, variation, ecoplus, pb, moves, nbm) VALUES" 
                          "(:eco,:opening,:variation,:ecoplus,:pb,:moves,:nbm)");
    QString ecoval=mValues.takeFirst();
    QString opening=mValues.takeFirst();
    //if (mEcoPlusCount.toQString()=="zz") mcountzz=true;
    if (ecoval == mLastECO ) 
    {
    if( mLastECO.isEmpty() ) { mLastECO=ecoval;} // Starting
    else ++(mEcoPlusCount);
    }
    else {
      mLastECO=ecoval;
      mEcoPlusCount.Raz();
    }
    
    QString variation,ecoplus;
    if (mValues.isEmpty()) 
    {
      variation="";
    }
    else 
    {
      variation=mValues.takeFirst();
    }
    QSqlQuery query;
    query.prepare(sqlreq);
    query.bindValue(":eco",ecoval);        
    query.bindValue(":opening",opening); 
    query.bindValue(":variation",variation);
    query.bindValue(":ecoplus",mEcoPlusCount.toQString());
    query.bindValue(":pb",FEN(mMoves));
    query.bindValue(":moves",mMoves.join(','));
    query.bindValue(":nbm",mMoves.count()); 
    query.exec();
 //   qDebug()<<query.lastError().text();
    
}
    
void EcoTableGeneration::setSqlHandler( QSqlDatabase *db)
    {
        mdb=db; 
        mdb->transaction();
    }



chess::PackedBoard EcoTableGeneration::BitBoard(QStringList moves)
{
    chess::Board board(chess::constants::STARTPOS);
    for ( QString  m : moves)  { 
       std::string utf8String = m.toUtf8().toStdString();
       chess::Move move =chess::uci::parseSan(board,std::string_view(utf8String));
       board.makeMove(move);
    }
    
    return chess::Board::Compact::encode(board);
}

QString EcoTableGeneration::FEN(QStringList moves)
{
    chess::Board board(chess::constants::STARTPOS);
    for ( QString  m : moves)  { 
       std::string utf8String = m.toUtf8().toStdString();
       chess::Move move =chess::uci::parseSan(board,std::string_view(utf8String));
       board.makeMove(move);
    }   
    return QString::fromStdString(board.getFen(false));
}
