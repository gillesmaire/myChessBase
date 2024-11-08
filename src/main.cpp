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

#include "utils.h"


QMap <QString,int> fontList;
QString InitWhiteSquareColor="#E6E6E6";
QString InitBlackSquareColor="#33653B";
QString InitWhitePieceColor="#FFD88B";
QString InitBlackPieceColor="#04151D";

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
   
    // Date of first use 
    
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

   
     fontList["Magnetic"]=QFontDatabase::addApplicationFont(":/Fonts/MAGNFONT.TTF");
     fontList["Leipzig"]=QFontDatabase::addApplicationFont(":/Fonts/LEIPFONT.TTF");
     fontList["Cases"]=QFontDatabase::addApplicationFont(":/Fonts/CASEFONT.TTF");
     fontList["Maya"]=QFontDatabase::addApplicationFont(":/Fonts/MAYAFONT.TTF");
     fontList["Chess-7"]=QFontDatabase::addApplicationFont(":/Fonts/Chess-7.TTF");
     fontList["Marroquin"]=QFontDatabase::addApplicationFont(":/Fonts/MARRFONT.TTF");
     fontList["Cheq"]=QFontDatabase::addApplicationFont(":/Fonts/CHEQ_TT.TTF");
     fontList["Alpha"]=QFontDatabase::addApplicationFont(":/Fonts/Alpha.ttf");
     fontList["OpenChessFont"]=QFontDatabase::addApplicationFont(":/Fonts/OpenChessFont.ttf");
     
     
    // Data base creation if not exists
    QString databasefile;
    
    QSqlDatabase db= Utils::PrepareDataBase(databasefile);
    
    MainWindow w;
    w.setDataBaseConnector(&db);
    w.setDataBaseName(databasefile);
    w.show();
    return a.exec();
}
