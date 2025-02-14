// GPL 3.0 License
// myChessBase Project
// Copyright (c) 2025 Gilles Maire <gilles@gillesmaire.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// THIS FILE IS AUTO GENERATED DO NOT CHANGE MANUALLY.
//
// Source: https://github.com/gillesmaire/myChessbase.git
//
//
// VERSION: 0.1
#include "limitedtextedit.h"

#include <QRegularExpression>

LimitedTextEdit::LimitedTextEdit(QWidget *parent)
    : QTextEdit(parent)
    , maxCharactersPerLine(80)
{
    connect (this,SIGNAL(textChanged()),this,SLOT(Empty()));
}

void LimitedTextEdit::keyPressEvent(QKeyEvent *event)
{
    QTextCursor cursor = textCursor();
    QString text = cursor.block().text();

    // Gestion des espaces (autorisé même en fin de ligne)
    if (event->key() == Qt::Key_Space) {
        // Vérifie la limite uniquement si on dépasse maxCharactersPerLine
        if (text.length() < maxCharactersPerLine || cursor.position() < cursor.block().length()) {
            QTextEdit::keyPressEvent(event);
        }
        return;
    }

    // Autorise les autres caractères tant que la ligne est sous la limite
    if (text.length() < maxCharactersPerLine) {
        QTextEdit::keyPressEvent(event);
    } else {
        event->ignore(); // Ignore l'entrée si la limite est atteinte
    }
}

void LimitedTextEdit::insertPlainText(const QString &text)
{
    QTextCursor cursor = textCursor();
    QStringList lines = text.split(QChar(0x2029));
    QString result;
    for (QString &line : lines) {
        if (line.length() > maxCharactersPerLine) {
            result += line.left(maxCharactersPerLine) + "\n";
        } else {
            result += line + "\n";
        }
    }
    QTextEdit::insertPlainText(result.trimmed());
    cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, text.length());
    setTextCursor(cursor);
}

void LimitedTextEdit::SetCursor(int i)
{
    // QString text = toPlainText();
    // QRegularExpression regex(R"(\d+\. )"); // Détecte les numéros de coups (ex: 1., 2., 3.)
    // QTextCursor cursor(document());
    
    // int moveCount = 0;
    // int pos = 0;
    
    // QTextStream stream(&text);
    // while (!stream.atEnd()) {
    //     QString word;
    //     stream >> word;
    //     // Ignorer les numéros de coups (1., 2., 3., etc.)
    //     if (regex.match(word).hasMatch()) {
    //         continue;
    //     }
    //     moveCount++;

    //     if (moveCount == i) {
    //        // cursor.setPosition(pos, QTextCursor::MoveAnchor);
    //         cursor.setPosition(pos);
    //         cursor.setPosition(QTextCursor::NextWord, QTextCursor::KeepAnchor);
    //         setTextCursor(cursor);
    //         return;
    //     }

    //     pos += word.length() + 1; // Prend en compte les espaces
    // }
}


void LimitedTextEdit::Empty() {
    emit IsEmpty(document()->isEmpty());
}

// int begin = ...
// int end = ...
// ...

// QTextCharFormat fmt;
// fmt.setBackground(Qt::yellow);

//QTextCursor cursor(edit->document());
// cursor.setPosition(begin, QTextCursor::MoveAnchor);
// cursor.setPosition(end, QTextCursor::KeepAnchor);
// cursor.setCharFormat(fmt);


