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



#ifndef FORMCONFIG_H
#define FORMCONFIG_H

#include <QWidget>

namespace Ui {
class FormConfig;
}
///
/// \brief The FormConfig class is the configuration windows fopr the application :
///  - First screen
///     - Colors of whie and black cases
///     - Colors of pieces
///     - Style of pieces
///     - DPI correction for the aspect ratio of square with ultrawide screen
///  - Second screen
///     - personnal information name; firstname elo title
///     - Language change   
///
class FormConfig : public QWidget
{
    Q_OBJECT

public:
    explicit FormConfig(QWidget *parent = nullptr);
    ~FormConfig();


private slots:
    ///
    /// \brief ChangeColor change color of white squares black squares black pieces and white pieces
    ///
    void ChangeColor(QString, QColor);
    ///
    /// \brief Save : save information in config files
    ///
    void Save();
    ///
    /// \brief ChangePiece set the current piece font
    /// \param name
    ///
    void ChangePiece(QString name );
    ///
    /// \brief SaveInformations save the informations modified for the future usage
    ///
    void SaveInformations();
    
private:
    Ui::FormConfig *ui;
    QFont mCurrentFont;
    ///
    /// \brief RedrawChessBoard : redraw the current chess board
    ///
    void RedrawChessBoard();
signals:
    ///
    /// \brief askRefresh configuration send askRefresh signal to modify the application on live
    ///
    void askRefresh();
};

#endif // FORMCONFIG_H
