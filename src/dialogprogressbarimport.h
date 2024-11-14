#ifndef DIALOGPROGRESSBARIMPORT_H
#define DIALOGPROGRESSBARIMPORT_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class DialogProgressBarImport;
}

class DialogProgressBarImport : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogProgressBarImport(QWidget *parent = nullptr);
    ~DialogProgressBarImport();
    void CountIncrement();
    void ClockStop();
    void ClockRaz();
    void updateCounterDisplay();
    
private:
    Ui::DialogProgressBarImport *ui;
    QTimer *mTimer;
    void ClockIncrement();
    int mTime=0;
    void Close();
    
};



#endif // DIALOGPROGRESSBARIMPORT_H
