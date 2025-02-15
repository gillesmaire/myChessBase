#ifndef FORMPGNEDITOR_H
#define FORMPGNEDITOR_H

#include <QWidget>
#include <QTextEdit>
#include <QTimer>

namespace Ui {
class FormPGNEditor;
}

class FormPGNEditor : public QWidget
{
    Q_OBJECT

enum HilightPosition{FIRST,BEFORE,AFTER,LAST};
enum StackedWidgetSubNavigation{PLAYSHOW,FENSHOW,NOSHOW};

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
    ///
    /// \brief  RemoveVariantsComments remove all the variants and comments from game moves
    /// \param  moves 
    /// \return the string with all the moves/
    ///
    static QString KeepMovesOnly(QString moves);
    ///
    /// \brief  RemoveResult : remove " 1-0" " 0-1" and " 1/2-1/2" frome the game moves
    /// \param  moves list of moves . Don't use for a PGN with player names etc but 
    ///         just used for the moves part
    /// \return the list of moves without result
    ///
    static QString RemoveResult(QString moves);

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
    /// \brief Clear save the value to be able to restore it and raz the 
    ///         linedit FEN to allow to fill
    ///
    void Clear();
    
    ///
    /// \brief  Paste this function read all the PGN records and fill the editor. 
    ///         The moves are copied on the Text editor but result is removed and
    ///         stored in result combobox
    ///
    void Paste();
    
    ///
    /// \brief MakeListVariantComments from content of PGN editor produces 2 lists 
    ///        1 - list of QMap indexed by move containing corresponding FEN
    ///        2 - list of QMap indexed by moce containing corresponding Comment
    /// \param pgn PGN who can contains variants and comments
    /// \param variants : reference on list of move with FEN
    /// \param cmments : refernce on list on move with comment or nag 
    ///
    /// 
    
void MakeListVariantComments(const QString &pgn, QList<QMap<QString, QString>> &variants, QList<QMap<QString, QString>> &comments, QList<QMap<QString, QString>> &nags);
    
    ///
    /// \brief setBold set Bold in the editor the I th move ( number of moves are skipped)
    /// \param i num number on move
    ///
void setBold(int i);

    ///
    /// \brief QuitPlayMode erase the play mode
    ///
void QuitStacked();

///
/// \brief SpeedSave save the value of Speed for automatics moves 
///
void SpeedSave();

///
/// \brief PlayModePause ask pause 
///
void PlayModePause();

///
/// \brief ChangeSpeed display the number of moves per minute in a spinbox 
///         without in read only mode
/// \param value the value
///
void ChangeSpeed(int value);
///
/// \brief UpdateTimerCounter changes TimerCounter  on each second
/// 
void UpdateTimerCounter();

///
/// \brief Reset TimerCounter 
///
void ResetTimerCounter();



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
    
    int PositionHilight=0;
};

QList <QMap<QString,QString>> mVariants;
QList <QMap<QString,QString>> mComments;
QList <QMap <QString,QString>> mNags;


///
/// \brief mListNav mListNav is a list of move when we navigate int game with the button < or << 
/// It is a subet of the game
//
///
QStringList mListNav;

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
    
    ///
    /// \brief Hilight Hilight the position number move on the QTextEdit t and in the variant variant number
    /// \param t : the texedit pointer
    /// \param position : position can be  FIRST, NEXT, BEFORE. LAST
    /// 
    ///
     void Hilight(QTextEdit *te, FormPGNEditor::HilightPosition pos);
    
    ///
    /// \brief parsePGN buggy function given by chatGPT cazy but usefull for functions.
    /// \param pgnText
    /// \return 
    ///
    GameData parsePGN(const QString &pgnText);
    
    ///
    /// \brief selectChessMove extend word selection for - + and 
    /// \param textEdit
    ///
    void selectChessMove(QTextEdit *textEdit);
    
    ///
    /// \brief posHilight is the start position of Hilight text in moves textedit
    ///
    int mPosHilight=0;
    ///
    /// \brief CharToSign convert 0-0 to 0_0 and other + = symbol
    ///        it is important to don't see - as a separator in QCursor methods
    /// \param list
    /// \return the QStringList converted
    ///
    QStringList CharToSign(QStringList list);
    
    ///
    /// \brief SignToChar reverse
    /// \param list
    /// \return the stringlist converted
    ///
    QStringList SignToChar(QStringList list);
    
    
    ///
    /// \brief CharToSign convert all - to _ 
    /// \param s
    /// \return 
    ///
    QString CharToSign(QString s);
    
    ///
    /// \brief SignToChar conver _ to - 
    /// \return the string converted
    ///
    QString SignToChar(QString);
    
    ///
    /// \brief mTimerMove is a timer to count the second per move
    ///
    QTimer *mTimerMove;
  
    int  mTimerCount=0;
};
#endif // FORMPGNEDITOR_H

