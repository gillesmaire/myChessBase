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
#include "utils.h"

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
    
    // Add a font in application 
    QFontDatabase::addApplicationFont(":/fonts/resources/Technology-Bold.ttf");
    
    // Data base creation if not exists
    QString databasefile;
    QSqlDatabase db= Utils::PrepareDataBase(databasefile);
    MainWindow w;
    w.setDataBaseConnector(&db);
    w.setDataBaseName(databasefile);
    w.show();
    return a.exec();
}
