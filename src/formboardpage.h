#ifndef FORMBOARDPAGE_H
#define FORMBOARDPAGE_H

#include <QWidget>

namespace Ui {
class FormBoardPage;
}

class FormBoardPage : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormBoardPage(QWidget *parent = nullptr);
    ~FormBoardPage();
    
private:
    Ui::FormBoardPage *ui;
};

#endif // FORMBOARDPAGE_H
