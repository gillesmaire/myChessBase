#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <formboardpage.h>
#include <formcounterpage.h>
#include <dialogprogressbarimport.h>
#include <formconfig.h>
#include <QFutureWatcher>
#include <QLabel>

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


private slots:
  
    ///
    /// \brief SaveDefaultUnivers when Tab Widget is modifed the value is stored. At the next time the program will
    ///        set thie univers.
    /// \param i
    ///
    void SaveDefaultUnivers(int i);
    void MyPreferences();

    

private:
    Ui::MainWindow *ui; 
    QFutureWatcher<void> mWatcher;

};

#endif // MAINWINDOW_H
