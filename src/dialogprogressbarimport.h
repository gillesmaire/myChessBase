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
    
private:
    Ui::DialogProgressBarImport *ui;
    QTimer *mTimer;
    void ClockIncrement();

    int mTime=0;
};

#endif // DIALOGPROGRESSBARIMPORT_H
