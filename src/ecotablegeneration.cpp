#include "ecotablegeneration.h"
#include <QSqlQuery>
#include <QSqlError>
#include "utils.h"

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
          "INSERT INTO ECO ( eco, opening, variation, ecoplus, moves, pb, nbm,  wins, losts, equals ) VALUES" 
                          "(:eco,:opening,:variation,:ecoplus,:moves,:pb,:nbm,:wins,:losts,:equals)");
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
    //query.bindValue(":fen",FEN(mMoves));
    query.bindValue(":pb", Utils::PackeBoard2ByteArray(BitBoard(mMoves)));
    query.bindValue(":moves",mMoves.join(' '));
    query.bindValue(":nbm",mMoves.count()); 
    query.bindValue(":wins",0); 
    query.bindValue(":losts",0); 
    query.bindValue(":equals",0); 
    query.exec();
    QString q;
    QMap<QString,QChar> list=Utils::ListPGNRecords();
    for (auto key:  list.keys() ){
        if ( key != "ECO" and key!= "ecoplus") 
        {
         QString type=(list[key]=='T')?"TEXT":"INTEGER";
         q+=QString("'%1' %2").arg(key,type)+",";
        }
    }
    QString qs1(QString("CREATE TABLE '%1%2' ('Id' INTEGER NOT NULL UNIQUE,MOVES NOT NULL,%3 PRIMARY KEY('Id' AUTOINCREMENT))")
    .arg(ecoval).arg(mEcoPlusCount.toQString()).arg(q));
    QSqlQuery qsq1(qs1);
    
    if ( !mStagingTableCreated ){
        QString qss(QString("CREATE TABLE 'Staging' ('Id' INTEGER NOT NULL UNIQUE,MOVES NOT NULL,%3 ECO, PRIMARY KEY('Id' AUTOINCREMENT))")
        .arg(q));
        mStagingTableCreated=true;
        QSqlQuery qqss(qss);
    }
    
    
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
