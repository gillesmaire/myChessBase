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
    connect(ui->lineEditFEN,SIGNAL(returnPressed()),this,SLOT(MAJBoardWithFen()));
    connect(ui->pushButtonFENReset,SIGNAL(pressed()),this, SLOT(Clear()));
    connect(ui->pushButtonFENLast,SIGNAL(pressed()),this, SLOT(LastFen()));
    connect(ui->Board,SIGNAL(SetCursor(int)),ui->textEditMoves,SLOT(SetCursor(int)));
    connect(ui->Board,SIGNAL(MovesModifiedFromChessBoard(QStringList)),this,SLOT(GetListMoves(QStringList)));
    connect(ui->Board,SIGNAL(FENFromChessBoard(QString)),this,SLOT(MAJFEN(QString)));
    
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

QStringList  FormPGNEditor::SignToChar(QStringList list){
    QStringList ret;
    for ( auto e:list)
      {
        e.replace("-","–");
        e.replace("=","＝");
        e.replace("+","＋");
        e.replace("*","✱");
        e.replace("/","⁄");
        ret<<e;
      }
    return ret;
}


QStringList FormPGNEditor::CharToSign(QStringList list){
    QStringList ret;
    for ( auto e:list)
      {
        e.replace("–","-");
        e.replace("＝","=");
        e.replace("＋","-");
        e.replace("✱","*");
        e.replace("⁄","/");
        ret<<e;
      }
    return ret;
    return ret;
}
void FormPGNEditor::GetListMoves( QStringList list)
{
    ui->textEditMoves->setText(Utils::NumberSanMoves(SignToChar(list)));
    
    QApplication::processEvents();  
    Hilight(ui->textEditMoves,LAST);
    
    // MakeListVariantComments(list.join(' '), mVariants,mComments,mNags);
}

void FormPGNEditor::Hilight(QTextEdit *textEdit,FormPGNEditor::HilightPosition pos)
{   QTextCharFormat format;
    QTextCursor cursor(textEdit->document());
    cursor.select(QTextCursor::Document);
    format.setFontWeight(QFont::Normal);
    cursor.mergeCharFormat(format);
    cursor.setPosition(mPosHilight);
    cursor.select(QTextCursor::WordUnderCursor);
    cursor.movePosition(QTextCursor::PreviousWord);
    if ( pos == LAST) {
        int count = 0;
        while (!cursor.atEnd()) {
            cursor.movePosition(QTextCursor::NextCharacter);
            QChar c = cursor.document()->characterAt(cursor.position());
            if (c == '(') {
                count++;
            } else if (c == ')') {
                if (count == 0) {
                    break; // Parenthèse fermante trouvée
                }
            count--;
            }
        }
        cursor.select(QTextCursor::WordUnderCursor);
        if (cursor.selectedText().isEmpty()) {
            //cursor.movePosition(QTextCursor::WordLeft);
            cursor.movePosition(QTextCursor::WordLeft,QTextCursor::KeepAnchor,2);
            qDebug()<<cursor.position();
            cursor.select(QTextCursor::WordUnderCursor);
            qDebug()<<cursor.position();
           }
        selectChessMove(textEdit);
        QTextCharFormat format;
        format.setFontWeight(QFont::Bold);
        cursor.mergeCharFormat(format);
        cursor.movePosition(QTextCursor::PreviousWord);
    }
    else if (pos==FIRST)
    {
      selectChessMove(textEdit);
        cursor.movePosition(QTextCursor::Start);
    }
    else if ( pos==AFTER)
    {
        if ( cursor.position() != QTextCursor::End) {
            cursor.select(QTextCursor::WordUnderCursor);
            bool integer;
            cursor.selectedText().toInt(&integer);
            if ( integer) cursor.movePosition(QTextCursor::NextWord,QTextCursor::MoveAnchor,1);
            else if ( cursor.selectedText()== " ") 
                cursor.movePosition(QTextCursor::NextWord,QTextCursor::MoveAnchor,3);
            else { cursor.movePosition(QTextCursor::NextWord,QTextCursor::MoveAnchor,1);
                   cursor.select(QTextCursor::WordUnderCursor);
                   QString selected2Text = cursor.selectedText();
                   cursor.selectedText().toInt(&integer);
                   if ( integer) 
                        cursor.movePosition(QTextCursor::NextWord,QTextCursor::MoveAnchor,1);
                   else cursor.movePosition(QTextCursor::NextWord,QTextCursor::MoveAnchor,0);
                    //cursor.movePosition(QTextCursor::NextWord,QTextCursor::MoveAnchor,1)
             }
         
            cursor.select(QTextCursor::WordUnderCursor);
         selectChessMove(textEdit);
            QTextCharFormat format;
            format.setFontWeight(QFont::Bold);
            cursor.mergeCharFormat(format);
        }
    }
    else if (pos==BEFORE)
    {
      qDebug()<<cursor.position()<<QTextCursor::Start;
        if (cursor.position()!= QTextCursor::Start) {
            // 2. Nf3 Nf6 or 2. Nf3
            QRegularExpression re("\\.");
            cursor.select(QTextCursor::WordUnderCursor);
            cursor.movePosition(QTextCursor::PreviousWord,QTextCursor::MoveAnchor,2);
            cursor.select(QTextCursor::WordUnderCursor);
            if (cursor.selectedText().contains(re))
                cursor.movePosition(QTextCursor::PreviousWord,QTextCursor::MoveAnchor,3);
            else 
                cursor.movePosition(QTextCursor::PreviousWord,QTextCursor::MoveAnchor,1);
            cursor.select(QTextCursor::WordUnderCursor); // e5   
         selectChessMove(textEdit);
            QTextCharFormat format;
            format.setFontWeight(QFont::Bold);
            cursor.mergeCharFormat(format);
        }
        
    }
    mPosHilight=cursor.position();
}





void FormPGNEditor::selectChessMove(QTextEdit* textEdit) {
    QTextCursor cursor = textEdit->textCursor();
    if (!cursor.hasSelection()) {
        // Grow the selection on left side while there is a valid car
        
        while (cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor)) {
            QChar c = cursor.selectedText().at(0);
            if (!c.isLetterOrNumber() && c != '-' && c != '+' && c != '#' && c != '=') {
                cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor); // Revenir à la dernière position valide
               
                break;
            }
             
        }
        // Grow the selection on right side while there is a valid car
        while (cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor)) {
            QChar c = cursor.selectedText().right(1).at(0);
            if (!c.isLetterOrNumber() && c != '-' && c != '+' && c != '#' && c != '=') {
                cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor);
               
                break;
            }
             
        }
    }
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
    if ( i == FormNavigationButton::First ) {ui->Board->goStart();Hilight(ui->textEditMoves,FIRST);}
    else if (i == FormNavigationButton::Last ) {ui->Board->goEnd();Hilight(ui->textEditMoves,LAST);}
    else if (i == FormNavigationButton::Before ) { ui->Board->goBack(); Hilight(ui->textEditMoves,BEFORE);}
    else if (i == FormNavigationButton::Next ) { ui->Board->goNext();Hilight(ui->textEditMoves,AFTER);}
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


void FormPGNEditor::setBold( int i) {
    QString text = ui->textEditMoves->toPlainText();
    QRegularExpression regex(R"(\b\d+\.\s*)"); 
    QStringList words = text.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts); // Sépare les mots
    QList<int> positions;
    int pos = 0;
    for (const QString &word : words) {
        if (!regex.match(word).hasMatch()) { 
            positions.append(pos);
        }
        pos += word.length() + 1; 
    }
    if (i <= 0 || i > positions.size()) return; 
    QTextCursor cursor = ui->textEditMoves->textCursor();
    cursor.setPosition(positions[i - 1]); 
    cursor.movePosition(QTextCursor::NextWord, QTextCursor::KeepAnchor); // Sélectionner le mot
    QTextCharFormat format;
    format.setFontWeight(QFont::Bold);
    cursor.mergeCharFormat(format);
 }
    
