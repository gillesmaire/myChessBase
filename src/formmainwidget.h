#ifndef FORMMAINWIDGET_H
#define FORMMAINWIDGET_H

#include <QWidget>

namespace Ui {
class FormMainWidget;
}

class FormMainWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormMainWidget(QWidget *parent = nullptr);
    ~FormMainWidget();
    
private:
    Ui::FormMainWidget *ui;
};

#endif // FORMMAINWIDGET_H
