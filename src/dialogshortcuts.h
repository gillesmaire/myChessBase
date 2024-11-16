#ifndef DIALOGSHORTCUTS_H
#define DIALOGSHORTCUTS_H

#include <QDialog>

namespace Ui {
class DialogShortCuts;
}

class DialogShortCuts : public QDialog
{
    Q_OBJECT

public:
    explicit DialogShortCuts(QWidget *parent = nullptr);
    ~DialogShortCuts();

private:
    Ui::DialogShortCuts *ui;
};

#endif // DIALOGSHORTCUTS_H
