#ifndef FORMCOUNTERPAGE_H
#define FORMCOUNTERPAGE_H

#include <QWidget>

namespace Ui {
class FormCounterPage;
}

class FormCounterPage : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormCounterPage(QWidget *parent = nullptr);
    ~FormCounterPage();
    void On();
    void Off();
    void IncremetentConversionCounter();
private:
    Ui::FormCounterPage *ui;
    QTimer *timer;
    void updateTime();
    bool mReady=false;
    int seconds=0;
};

#endif // FORMCOUNTERPAGE_H
