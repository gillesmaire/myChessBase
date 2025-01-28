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
#ifndef LIMITEDTEXTEDIT_H
#define LIMITEDTEXTEDIT_H

#include <QTextEdit>
#include <QTextBlock>
///
/// \brief The LimitedTextEdit class this classe limit a QTextEdit on 80 caracters
///
class LimitedTextEdit : public QTextEdit {
    Q_OBJECT

public:
    explicit LimitedTextEdit(QWidget* parent = nullptr) 
        : QTextEdit(parent), maxCharactersPerLine(80) {}


    void keyPressEvent(QKeyEvent* event) override {
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

    void insertPlainText(const QString& text)  {
        QTextCursor cursor = textCursor();
        QStringList lines = text.split(QChar(0x2029));
        QString result;

        // Limite chaque ligne à maxCharactersPerLine caractères
        for (QString& line : lines) {
            if (line.length() > maxCharactersPerLine) {
                result += line.left(maxCharactersPerLine) + "\n";
            } else {
                result += line + "\n";
            }
        }

        // Insère le texte modifié
        QTextEdit::insertPlainText(result.trimmed());

        // Restaure la position du curseur après insertion
        cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, text.length());
        setTextCursor(cursor);
    }

private:
    int maxCharactersPerLine; // Limitation des caractères par ligne
};
#endif // LIMITEDTEXTEDIT_H
