#ifndef FORMNAVIGATIONBUTTON_H
#define FORMNAVIGATIONBUTTON_H

#include <QWidget>

namespace Ui {
class FormNavigationButton;
}

class FormNavigationButton : public QWidget
{
    Q_OBJECT


public:
    enum Action { First,Before,Play,Next,Last,Reverse,NumberCase,FEN,RemoveLast};
    explicit FormNavigationButton(QWidget *parent = nullptr);
    ~FormNavigationButton();
    void dispatch();
private:
    Ui::FormNavigationButton *ui;
signals:
    void button( int action);
};

#endif // FORMNAVIGATIONBUTTON_H
