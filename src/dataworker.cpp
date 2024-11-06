#include "dataworker.h"
#include "myvisitor.h"
#include "chess.hpp"
#include <string>
#include <fstream>


DataWorker::DataWorker( QString filename ,QSqlDatabase *db): mDb(db),mFileName(filename)
{
    
}

void DataWorker::InsertData()
{
    auto file_stream=std::ifstream(mFileName.toLatin1());
    auto vis =std::make_unique<MyVisitor>();
    vis->setConnection(mDb);
//    vis->setProgressBar(mDb);
    if ( !mDb->transaction()) qDebug("Connection problem !");
    pgn::StreamParser parser(file_stream);
    parser.readGames(*vis);
    if  (! mDb->commit())
    {
        qDebug() << "Failed to commit";
        mDb->rollback();
    }
    vis->StopChrono(); 
}

DataWorker::~DataWorker()
{
    
}
