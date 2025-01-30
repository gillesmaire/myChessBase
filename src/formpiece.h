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
#ifndef FORMPIECE_H
#define FORMPIECE_H

#include <QWidget>

namespace Ui {
class FormPiece;
}

///
/// \brief The FormPiece class this class display a piece in a Widget. It is sueful for promote
///        display piece for example
///
class FormPiece : public QWidget
{
    Q_OBJECT

public:
    explicit FormPiece(QWidget *parent = nullptr);
    ~FormPiece();
    ///
    /// \brief setPiece define the piece by name, Famylyfont and color
    /// \param piece
    /// \param FamilyFont
    /// \param color
    ///
    void setPiece(QString piece, QString FamilyFont, QColor color);

private:
    Ui::FormPiece *ui;
    QString mPiece;
    QString mFamilyFont;
    QColor  mColor;
};

#endif // FORMPIECE_H
