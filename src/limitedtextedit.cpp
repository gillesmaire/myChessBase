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



void LimitedTextEdit::SetCursor(int i) {
  
    
    
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


// int begin = ...
// int end = ...
// ...

// QTextCharFormat fmt;
// fmt.setBackground(Qt::yellow);

//QTextCursor cursor(edit->document());
// cursor.setPosition(begin, QTextCursor::MoveAnchor);
// cursor.setPosition(end, QTextCursor::KeepAnchor);
// cursor.setCharFormat(fmt);


