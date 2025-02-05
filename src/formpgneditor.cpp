#include "formpgneditor.h"
#include "ui_formpgneditor.h"
#include "utils.h"
#include <QDate>
#include <QSettings>
#include "calendardialog.h"
#include "nag.h"
#include "QRegularExpression"

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
    mFENSaved;
    ui->lineEditFEN->setText(mFENSaved);
}

void FormPGNEditor::MAJFEN(QString fen)
{
  ui->lineEditFEN->setText(fen);
}

void FormPGNEditor::MAJBoardWithFen()
{
    mFENSaved=ui->lineEditFEN->text();
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
    ui->dateEdit->setDate(date);   
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

