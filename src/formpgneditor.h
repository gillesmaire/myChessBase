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
    bool FENShown=false;
    
public slots:
    
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


    void showFEN();

    void MAJFEN(QString FEN);

    void MAJBoardWithFen();
    ///
    /// \brief LastFen set the last FEN 
    ///
    void LastFen();
    
    ///
    /// \brief Clear save the value to be able to restaure it and raz the 
    ///         linedit FEN to allow to fill
    ///
    void Clear();
    
    void Paste();

private:


struct GameData {
    QString whiteFirstname;
    QString whiteName;
    int whiteElo = 0;
    QString whiteFideID;
    QString whiteTitle;
    QString blackFirstname;
    QString blackName;
    int blackElo = 0;
    QString blackFideID;
    QString blackTitle;
    QString site;
    QString event;
    QString date;
    QString round;
    QString ecoCode;
    QString result;
    QString moves;
};

  
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
    ///
    /// \brief mFENSaved when FEN is shown we save the FEN in mFENSaved 
    ///        to be restore with button restore
    ///
    QString mFENSaved;
    
    
    GameData parsePGN(const QString &pgnText);

    
    
};

#endif // FORMPGNEDITOR_H

