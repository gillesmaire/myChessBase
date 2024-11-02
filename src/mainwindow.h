#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <formboardpage.h>
#include <formcounterpage.h>
#include <dialogprogressbarimport.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setDataBaseConnector(QSqlDatabase *connection);
    void setDataBaseName(QString file);
    void IncrementCounter();
private:
    Ui::MainWindow *ui; 
    QSqlDatabase *mConnection;
    QString mDataBaseFile;
    int Converted=0;
    void LoadPGNFile();
    void ShowInformations();
    void About();
    void RemoveDatabase();
    FormCounterPage *mFormCounterPageptr;
    FormBoardPage *mFormBoardPageptr;
    DialogProgressBarImport *mProgressBar;
};
#endif // MAINWINDOW_H
