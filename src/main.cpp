#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QSettings>
#include <QFileInfo>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMultiMap>
#include <QFontDatabase>
#include <QMap>
#include <chess.hpp>
#include "utils.h"
#include <QAtomicInt>

QMap <QString,int> fontList;
QString InitWhiteSquareColor="#E6E6E6";
QString InitBlackSquareColor="#33653B";
QString InitWhitePieceColor="#FFD88B";
QString InitBlackPieceColor="#04151D";
QString InitSideToPlayColor="#0055ff";
QString InitToPlayColor="#FF0000";
QString InitPieceFont="Maya";
QMap<QString,chess::PackedBoard> PackedBoards;
QMap<QString,QMap<QString,QChar>> Pieces;
QAtomicInt atct(0); // to be delete
QStringList FavouriteOpenings;


///
////// \brief main name of the program
////// \param argc not yet implemented
////// \param argv
////// \return 


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // Informations for QSettings
    
    QCoreApplication::setOrganizationName("myChessBase");
    QCoreApplication::setOrganizationDomain("myChessBase");
    QCoreApplication::setApplicationName("myChessBase");
   
    
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QSettings s;
    if (s.value("InitDate").isNull())
        s.setValue("InitDate",QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss"));
    
    
    // Translation of the program
    
    
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "myChessBase_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
     
   // Load Fonts 

   
     fontList["Magnetic"]=QFontDatabase::addApplicationFont(":/Fonts/Magnetic.ttf");
     fontList["Leipzig"]=QFontDatabase::addApplicationFont(":/Fonts/Leipzig.ttf");
     fontList["Cases"]=QFontDatabase::addApplicationFont(":/Fonts/Cases.ttf");
     fontList["Maya"]=QFontDatabase::addApplicationFont(":/Fonts/Maya.ttf");
     fontList["Chess-7"]=QFontDatabase::addApplicationFont(":/Fonts/Chess-7.ttf");
     fontList["Marroquin"]=QFontDatabase::addApplicationFont(":/Fonts/Marroquin.ttf");
     fontList["Cheq"]=QFontDatabase::addApplicationFont(":/Fonts/Cheq.ttf");
     fontList["Alpha"]=QFontDatabase::addApplicationFont(":/Fonts/Alpha.ttf");
     fontList["OpenChessFont"]=QFontDatabase::addApplicationFont(":/Fonts/OpenChessFont.ttf");
     
     
   
    
    MainWindow w;
    w.show();
    return a.exec();
}
