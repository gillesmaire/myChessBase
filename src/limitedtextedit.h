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
    explicit LimitedTextEdit(QWidget* parent = nullptr);
    void keyPressEvent(QKeyEvent* event) override;

    void insertPlainText(const QString& text);

private:
    int maxCharactersPerLine; // Limitation des caractères par ligne
private slots:
    void SetCursor(int i);
    void Empty();
signals:
    void IsEmpty(bool empty);
};
#endif // LIMITEDTEXTEDIT_H
