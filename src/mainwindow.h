#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <formboardpage.h>
#include <formcounterpage.h>
#include <dialogprogressbarimport.h>
#include <QFutureWatcher>
#include <QLineEdit>
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
static void LoadPGNFileConcurrent(QString filename, QSqlDatabase *con,DialogProgressBarImport *progressbar);
private slots:
    void ModifyColor(QColor whitesquarecolor, QColor blacksquarecolor);
private:
    Ui::MainWindow *ui; 
    QSqlDatabase *mConnection;
    QString mDataBaseFile;
    int Converted=0;
    bool mFlipBoard=false;
    void LoadPGNFile();
    QFutureWatcher<void> mWatcher;
    void ShowInformations();
    void About();
    void RemoveDatabase();
    void FlipBoard();
    FormCounterPage *mFormCounterPageptr;
    FormBoardPage *mFormBoardPageptr;
    DialogProgressBarImport *mProgressBar;
    void Configuration();
    void ShowFen(bool);
    QString getFen();
    bool mFENShown=false;
    QLineEdit *mFEN;
};
#endif // MAINWINDOW_H
