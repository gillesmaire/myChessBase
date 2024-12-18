#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <formboardpage.h>
#include <formcounterpage.h>
#include <dialogprogressbarimport.h>
#include <QFutureWatcher>
#include "dialogconfiguration.h"

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
    bool getFlipBoard(){ return mFlipBoard ;}
private slots:
    void Update();
    void ShoShortCuts();
    void SaveCaseNumbers();
    void ShowVariation(QString ECO, QString opening, QString variation, QString ecoplus, QString moves);
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
    void SuppressDataBaseGames();
    void SuppressDataBase();
    void FlipBoard();
    FormCounterPage *mFormCounterPageptr;
    FormBoardPage *mFormBoardPageptr;
    DialogProgressBarImport *mProgressBar;
    DialogConfiguration *mDialogConfiguration;
    void Configuration();
    void ShowFen(bool);
    QString getFen();
    bool mFENShown=false;
    QLineEdit *mFEN;
    ///
    /// \brief ActiveWidget set the Stacked Widget in the correspondant widget
    ///
    void ActiveWidget();
    ///
    /// \brief goStart called when the button go start is clicked. We need to inform chesssBoard and PGNEditor
    ///
    void goStart();
    ///
    /// \brief goBackcalled when the button go back is clicked. We need to inform chesssBoard and PGNEditor
    ///
    void goBack();
    void MyPreferences();
protected:
    void resizeEvent(QResizeEvent *e);

};


#endif // MAINWINDOW_H
