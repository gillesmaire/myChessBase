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
    void GetListMoves(QStringList list);

   

private:
    Ui::FormPGNEditor *ui;
    
    void Reset();
    ///
    /// \brief FormAutoFillBlack auto fill black records from personnal informations (name, firsname ,elo...)
    ///
    void FormAutoFillBlack(); 
    ///
    /// \brief FormAutoFillWhite auto fill white records from personnal informations (name, firsname ,elo...)
    ///
    void FormAutoFillWhite();
    ///
    /// \brief SelectDateFromCalendar allow to choose date not only with a widget date but with a true calendar to
    /// see the year, the week, the month
    ///
    void SelectDateFromCalendar();
    ///
    /// \brief AddNag : add ! ? or #12 information about moves
    ///
    void AddNag();
    ///
    /// \brief DelNag suppress a Nag is nag is under the cursor
    ///
    void DelNag();
    ///
    /// \brief AddComment add comment in a Game
    ///
    void AddComment();
    ///
    /// \brief DelComment del the comment around tu cursor position
    ///
    void DelComment();
signals:
    ///
    /// \brief showFen signal sent to show FEN
    /// 
    ///
    void showFen();
};

#endif // FORMPGNEDITOR_H
