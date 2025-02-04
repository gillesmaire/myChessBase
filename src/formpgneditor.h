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
    
public slots:
    ///
    /// \brief setFen Show FEN on ChessBoard
    /// \param FEN a valid or Invalid FEN to show on the Board
    ///
    void setFen(QString FEN);
    
    ///
    /// \brief AskRefresh slot to ask to ChessBoard to refresh all this init parameters
    ///
    void AskRefresh();
    
private slots:
    ///
    /// \brief Go  depends of value of button 
    ///     -  FormNavigationButton::First  => ui->Board->goStart()
    ///     -  FormNavigationButton::Last   => ui->Board->goEnd()
    ///     -  FormNavigationButton::Before => ui->Board->goBack()
    ///     -  FormNavigationButton::Next   => ui->Board->goNext()
    ///     -  FormNavigationButton::Reverse=> ui->Board->flipBoard(!ui->Board->flipped())
    ///     -  FormNavigationButton::NumberCase=> ui->Board->setNumberCase
    ///
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
