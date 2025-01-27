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
    void SetListMove(QString listmove);
    ~FormPGNEditor();
    ///
    /// \brief getListMove return the text in que QTexEdit ie list of moves
    /// \return 
    ///
    QString getListMove();
    void EraseBlackPlayer();
    void EraseWhitePlayer();

private slots:
    void Go(int i);

private:
    Ui::FormPGNEditor *ui;
    void Reset();
    void FormAutoFillBlack();
    void FormAutoFillWhite();
signals:
    void showFen();
};

#endif // FORMPGNEDITOR_H
