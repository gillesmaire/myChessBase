#ifndef FORMNAVIGATIONBUTTON_H
#define FORMNAVIGATIONBUTTON_H


#include <QWidget>
#include <QResizeEvent>
#include <QTimer>

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
    ///
    /// \brief dispatch calculate action 
    ///
    void dispatch();
    ///
    /// \brief modePause it true ask a pause if false ask to play
    /// \param mode
    ///
    void modePause(bool mode) ;
private:
    Ui::FormNavigationButton *ui;
    QTimer *mTimer ;
    int mCount=0;
    int speed;
    

protected:
    ///
    /// \brief resizeEvent not used. Used for test
    /// \param e
    ///
    void resizeEvent(QResizeEvent *e) override;
signals:
    ///
    /// \brief button when a button is pressed this signal is sent
    /// \param action
    ///
    void button( int action);
    
    
public slots:
    ///
    /// \brief SetUnsetPlayButton : the play button is not displayed, but when it receive signal 
    ///         it becile visible
    ///
    void SetUnsetPlayButton( bool);
    ///
    /// \brief AutoPlay autoplay start the timer who will call next move
    ///
    void AutoPlay();
    ///
    /// \brief ChangeSpeed is called to change the speed of move
    ///
    void ChangeSpeed(int);

};
#endif // FORMNAVIGATIONBUTTON_H
