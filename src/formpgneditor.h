#ifndef FORMPGNEDITOR_H
#define FORMPGNEDITOR_H

#include <QWidget>

namespace Ui {
class FormPGNEditor;
}

class FormPGNEditor : public QWidget
{
    Q_OBJECT

public:
    explicit FormPGNEditor(QWidget *parent = nullptr);
    ~FormPGNEditor();

private slots:
    void Go(int i);

private:
    Ui::FormPGNEditor *ui;
};

#endif // FORMPGNEDITOR_H
