#include "formpgneditor.h"
#include "ui_formpgneditor.h"
#include "utils.h"
#include "calendardialog.h"
#include "nag.h"

#include "QRegularExpression"
#include <QClipboard>
#include <QDate>
#include <QSettings>
#include <QRegularExpression>
#include "chess.hpp"

FormPGNEditor::FormPGNEditor(QWidget *parent)
    : QWidget(parent),ui(new Ui::FormPGNEditor)
{
    ui->setupUi(this);
    ui->comboBoxResult->setCurrentText("?");
    connect(ui->pushButtonReset,&QPushButton::clicked,this,&FormPGNEditor::Reset);
    connect(ui->pushButtonBlackYou,&QPushButton::clicked,this,&FormPGNEditor::FormAutoFillBlack);
    connect(ui->pushButtonWhiteYou,&QPushButton::clicked,this,&FormPGNEditor::FormAutoFillWhite);
    connect(ui->widgetNavigation,SIGNAL(button(int)),this,SLOT(Go(int)));
    connect(ui->pushButtonEraseWhitePlayer,&QPushButton::clicked,this,&FormPGNEditor::EraseWhitePlayer);
    connect(ui->pushButtonEraseBlackPlayer,&QPushButton::clicked,this,&FormPGNEditor::EraseBlackPlayer);
    connect(ui->toolButtonCalendar,&QToolButton::clicked,this,&FormPGNEditor::SelectDateFromCalendar);
    connect(ui->pushButtonAddNag,&QPushButton::clicked,this,&FormPGNEditor::AddNag);
    connect(ui->pushButtonDeleteNag,&QPushButton::clicked,this,&FormPGNEditor::DelNag);
    connect(ui->pushButtonAddComment,&QPushButton::clicked,this,&FormPGNEditor::AddComment);
    connect(ui->pushButtonDeleteComment,&QPushButton::clicked,this,&FormPGNEditor::DelComment);
    connect(ui->pushButtonPastePGN,&QPushButton::clicked,this,&FormPGNEditor::Paste);
    connect(ui->Board,SIGNAL(MovesModifiedFromChessBoard(QStringList)),this,SLOT(GetListMoves(QStringList)));
    connect (ui->Board,SIGNAL(FENFromChessBoard(QString)),this,SLOT(MAJFEN(QString)));
    connect (ui->lineEditFEN,SIGNAL(returnPressed()),this,SLOT(MAJBoardWithFen()));
    connect (ui->pushButtonFENReset,SIGNAL(pressed()),this, SLOT(Clear()));
    connect (ui->pushButtonFENLast,SIGNAL(pressed()),this, SLOT(LastFen()));
    
    ui->spinBoxBlackElo->setDigitNumber(4);
    ui->spinBoxWhiteElo->setDigitNumber(4);
    ui->comboBoxNags->addItems(Nag::getNagListNumbered());
    ui->textEditMoves->setReadOnly(true);
    ui->textEditMoves->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
    FENShown=true;
    showFEN();
    ui->lineEditFEN->setText("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    mFENSaved=ui->lineEditFEN->text();
}

void FormPGNEditor::Clear()
{
    mFENSaved=ui->lineEditFEN->text();
    ui->lineEditFEN->clear();
}


void FormPGNEditor::LastFen()
{   
    ui->lineEditFEN->setText(mFENSaved);
}

void FormPGNEditor::MAJFEN(QString fen)
{
  ui->lineEditFEN->setText(fen);
}

void FormPGNEditor::MAJBoardWithFen()
{
    QString fen=ui->lineEditFEN->text();
    QRegularExpression fenRegex(R"(^\s*([rnbqkpRNBQKP1-8]{1,8}/){7}[rnbqkpRNBQKP1-8]{1,8} [wb] (-|[KQkq]+) (-|[a-h][36]) \d+ \d+\s*$)");
    if  ( ! fenRegex.match(fen).hasMatch()) {
        ui->lineEditFEN->setText("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    }
    else ui->lineEditFEN->setText(fen);

    ui->Board->setFEN(ui->lineEditFEN->text());
}

void FormPGNEditor::GetListMoves( QStringList list)
{
    ui->textEditMoves->setText(Utils::NumberSanMoves(list));
}

void FormPGNEditor::showFEN() 
{
    FENShown=!FENShown;
    ui->lineEditFEN->setVisible(FENShown);
    ui->pushButtonFENReset->setVisible(FENShown);
    ui->pushButtonFENLast->setVisible(FENShown);
}

void FormPGNEditor::SelectDateFromCalendar()
{
    
    CalendarDialog dialog(this);
    dialog.exec();
    QDate date=dialog.selectedDate();
    if ( dialog.status()) ui->dateEdit->setDate(date);   
}

void FormPGNEditor::Go(int i)
{
    if ( i == FormNavigationButton::First ) ui->Board->goStart();
    else if (i == FormNavigationButton::Last ) ui->Board->goEnd();
    else if (i == FormNavigationButton::Before ) ui->Board->goBack();
    else if (i == FormNavigationButton::Next ) ui->Board->goNext();
    else if (i== FormNavigationButton::Reverse) ui->Board->flipBoard(!ui->Board->flipped());
    else if (i== FormNavigationButton::NumberCase) ui->Board->setNumberCase(!ui->Board->casesNumbered());
    else  if (i== FormNavigationButton::FEN){  showFEN();}
    
}

FormPGNEditor::~FormPGNEditor()
{
    delete ui;
}

QString FormPGNEditor::getListMove() 
{
    return ui->textEditMoves->toPlainText();
}

void FormPGNEditor::EraseBlackPlayer() 
{
    ui->lineEditBlackFirstName->clear();
    ui->lineEditBlackName->clear();
    ui->spinBoxBlackElo->setValue(0);
    ui->spinBoxBlackFideID->setValue(0);
    ui->comboBoxBlackTitle->setCurrentIndex(0);

}

void FormPGNEditor::EraseWhitePlayer() 
{
    ui->lineEditWhiteFirstName->clear();
    ui->lineEditWhiteName->clear();
    ui->spinBoxWhiteElo->setValue(0);
    ui->spinBoxWhiteFideID->setValue(0);
    ui->comboBoxBlackTitle->setCurrentIndex(0);
}

void FormPGNEditor::AskRefresh() {ui->Board->askReloadConfiguration();}

void FormPGNEditor::SetListMove(QString listmove)
{
    ui->textEditMoves->clear();
    //ui->textEditMoves->setText(Utils::NumberSanMoves(listmove.split(" ")));
    ui->textEditMoves->setText(Utils::NumberSanMoves(listmove.split(" ")));
    
}


void FormPGNEditor::Reset()
{
  ui->spinBoxBlackElo->setValue(0);
  ui->spinBoxBlackFideID->setValue(0);
  ui->lineEditBlackFirstName->clear();
  ui->lineEditBlackName->clear();
  ui->spinBoxBlackElo->setValue(0);
  ui->comboBoxBlackTitle->setCurrentIndex(0);
  
  
  ui->spinBoxWhiteElo->setValue(0);
  ui->spinBoxWhiteFideID->setValue(0);
  ui->lineEditWhiteFirstName->clear();
  ui->lineEditWhiteName->clear();
  ui->spinBoxWhiteElo->setValue(0);
   ui->comboBoxWhiteTitle->setCurrentIndex(0);
 
  
  ui->textEditMoves->clear();
  ui->comboBoxResult->setCurrentIndex(0);
  ui->lineEditECO->clear();
  ui->lineEditEvent->clear();
 
 // ui->dateEdit->setDate(QDate::currentDate());
  ui->lineEditSite->clear();
  ui->lineEditRound->clear();
}

void FormPGNEditor::FormAutoFillBlack() 
{
    QSettings s;
    ui->spinBoxBlackElo->setValue(s.value("YourELO").toInt());
    ui->spinBoxBlackFideID->setValue(s.value("YourFideID").toInt());
    ui->lineEditBlackFirstName->setText(s.value("YourFirstname").toString());
    ui->lineEditBlackName->setText(s.value("YourName").toString());
    ui->comboBoxBlackTitle->setCurrentText(s.value("YourTitle").toString());
}

void FormPGNEditor::FormAutoFillWhite()
{
    QSettings s;
    ui->spinBoxWhiteElo->setValue(s.value("YourELO").toInt());
    ui->spinBoxWhiteFideID->setValue(s.value("YourFideID").toInt());
    ui->lineEditWhiteFirstName->setText(s.value("YourFirstname").toString());
    ui->lineEditWhiteName->setText(s.value("YourName").toString());
    ui->comboBoxWhiteTitle->setCurrentText(s.value("YourTitle").toString());
}


void FormPGNEditor::AddNag()
{
    QString str= Nag::getNag(ui->comboBoxNags->currentText());
    if (str.isEmpty()) return ; 
    QTextCursor cursor = ui->textEditMoves->textCursor();
    int pos=cursor.position();
    qDebug()<<"addnag"<<ui->textEditMoves->document()->characterAt(pos);
    if ( pos > 0 &&  ui->textEditMoves->document()->characterAt(pos) == QChar(0x2029)  ) {  
        cursor.movePosition(QTextCursor::Right);
        cursor.insertText(" ");
     }
     cursor.insertText(str);
     ui->textEditMoves->setTextCursor(cursor);  
}

void FormPGNEditor::DelNag()
{
    if ( Nag::isNag(ui->textEditMoves)) 
    {
        QTextCursor cursor = ui->textEditMoves->textCursor();
        cursor.select(QTextCursor::WordUnderCursor); 
        if (!cursor.selectedText().isEmpty()) 
           {
           qDebug()<<"delnag"<<cursor.selectedText();
                cursor.removeSelectedText();
           }
    }
}

void FormPGNEditor::AddComment()
{
    if (ui->lineEditComment->text().isEmpty()) return;
    QString text=QString(" {%1} ").arg(ui->lineEditComment->text());
     ui->textEditMoves->insertPlainText(text);
}


void FormPGNEditor::DelComment()
{
    QTextCursor cursor = ui->textEditMoves->textCursor(); 
    QString content = ui->textEditMoves->toPlainText();  
    int cursorPosition = cursor.position(); 
    int start = -1;
    int end = -1;
    for (int i = cursorPosition - 1; i >= 0; --i) {
        if (content[i] == '{') {
            start = i;
            break;
        }
    }
    for (int i = cursorPosition; i < content.length(); ++i) {
        if (content[i] == '}') {
            end = i;
            break;
        }
    }

    if (start != -1 && end != -1 && start < end) {
        content.remove(start, end - start + 1); 
        ui->textEditMoves->setPlainText(content); 
        cursor.setPosition(start);
        ui->textEditMoves->setTextCursor(cursor);
    }
}

FormPGNEditor::GameData FormPGNEditor::parsePGN(const QString &pgnText)
{
     GameData gameData;
    QRegularExpression regex("\\[([^\"]+) \"([^\"]+)\"]");
    QRegularExpressionMatchIterator matches = regex.globalMatch(pgnText);
    QMap<QString, QString> fields;

    while (matches.hasNext()) {
        QRegularExpressionMatch match = matches.next();
        if (match.hasMatch()) {
            fields[match.captured(1)] = match.captured(2);
        }
    }

    gameData.whiteName = fields.value("White", "");
    gameData.whiteFirstname = fields.value("WhiteFirstName", "");
    gameData.whiteElo = fields.value("WhiteElo", "0").toInt();
    gameData.whiteFideID = fields.value("WhiteFideId", "");
    gameData.whiteTitle = fields.value("WhiteTitle", "");

    gameData.blackName = fields.value("Black", "");
    gameData.blackFirstname = fields.value("BlackFirstName", "");
    gameData.blackElo = fields.value("BlackElo", "0").toInt();
    gameData.blackFideID = fields.value("BlackFideId", "");
    gameData.blackTitle = fields.value("BlackTitle", "");

    gameData.site = fields.value("Site", "");
    gameData.event = fields.value("Event", "");
    gameData.date = fields.value("Date", "");
    gameData.round = fields.value("Round", "");
    gameData.ecoCode = fields.value("ECO", "");
    gameData.result = fields.value("Result", "");

    // Extraction des coups avec commentaires et variantes
    QRegularExpression movesRegex("\\n\\n(.*)", QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatch movesMatch = movesRegex.match(pgnText);
    if (movesMatch.hasMatch()) {
        gameData.moves = movesMatch.captured(1).trimmed();
    }
    
    return gameData;
}

///
/// \brief Paste paste a PGN in the Editor
///
void FormPGNEditor::Paste() 
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    GameData game = parsePGN(clipboard->text());
    if ( game.whiteFirstname.isEmpty() && !game.whiteName.isEmpty() && game.whiteName.contains(',')) {
         QStringList g=game.whiteName.split(',');
         game.whiteName=g.first().trimmed();
         g.pop_front();
         game.whiteFirstname=g.join(' ').trimmed();
      }
    ui->lineEditWhiteName->setText(game.whiteName.trimmed());
    ui->lineEditWhiteFirstName->setText(game.whiteFirstname.trimmed());
    if ( game.blackFirstname.isEmpty() && !game.blackName.isEmpty() && game.blackName.contains(',')) {
         QStringList g=game.blackName.trimmed().split(',');
         game.blackName=g.first().trimmed();
         g.pop_front();
         game.blackFirstname=g.join(' ').trimmed();
      }
    ui->lineEditBlackName->setText(game.blackName.trimmed());
    ui->lineEditBlackFirstName->setText(game.blackFirstname.trimmed());
    
    ui->lineEditECO->setText(game.ecoCode.trimmed());
    ui->lineEditEvent->setText(game.event.trimmed());
    ui->lineEditRound->setText(game.round.trimmed());
    ui->lineEditSite->setText(game.site.trimmed());   
    ui->textEditMoves->setPlainText(game.moves.trimmed());
    ui->comboBoxResult->setCurrentText(game.result.trimmed());
    QStringList D=game.date.split('.');
    bool OK;
    qDebug()<<D;
    if (D.count()==3)
    {
        QDate dd(D.at(0).toInt(&OK),D.at(1).toInt(&OK),D.at(2).toInt(&OK));
        ui->dateEdit->setDate(dd);
    }
}

void FormPGNEditor::MakeListVariantComments(const QString &pgn,
                                            QList<QMap<QString, QString> > &variants,
                                            QList<QMap<QString, QString> > &comments,
                                            QList<QMap<QString, QString> > &nags)
{
    
    QRegularExpression variantRegex("\\(([^()]+)\\)");
    QRegularExpression commentRegex("\\{([^{}]+)\\}");
    QRegularExpression nagRegex("\\$(\\d+)");
    QRegularExpression moveNumberRegex("\\b\\d+\\."); // Supprimer les numéros de coups

    QString cleanPgn = pgn;
    cleanPgn.remove(moveNumberRegex);

    QStringList moves = cleanPgn.split(" ", Qt::SkipEmptyParts);
    
    QString currentFEN =constants::STARTPOS ; // Initialisation du FEN
    Board b(constants::STARTPOS);
    for (const QString &move : moves) {
        QMap<QString, QString> variantEntry, commentEntry, nagEntry;

        QRegularExpressionMatch variantMatch = variantRegex.match(move);
        if (variantMatch.hasMatch()) {
            variantEntry["variant"] = variantMatch.captured(1).trimmed();
        }

        QRegularExpressionMatch commentMatch = commentRegex.match(move);
        if (commentMatch.hasMatch()) {
            commentEntry["comment"] = commentMatch.captured(1).trimmed();
        }

        QRegularExpressionMatch nagMatch = nagRegex.match(move);
        if (nagMatch.hasMatch()) {
            nagEntry["nag"] = nagMatch.captured(1).trimmed();
        }

        if (!move.contains("{") && !move.contains("(")
            && !move.contains("$")) {
            Utils::deduceMove(b,move);
            currentFEN =QString::fromStdString(b.getFen());
        }
        variantEntry["FEN"] = currentFEN;

        variants.append(variantEntry);
        comments.append(commentEntry);
        nags.append(nagEntry);
    }
}
