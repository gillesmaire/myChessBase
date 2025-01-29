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

#ifndef CHESBOARDCURSOR_H
#define CHESBOARDCURSOR_H
#include <QCursor>
#include <chessboard.h>

class ChesBoardCursor
{
public:
    ///
    /// \brief SetChessBoardCursor set the ChessBoardCursor with a hand
    /// \return 
    ///
    static QCursor SetChessBoardCursor();
    ///
    /// \brief getCursor build and return a cursor on click on a piece. It mus have some argument
    /// \param sizetile    : the size of square
    /// \param font        : the font name (or family) . If Family is 'chess something' it is translated to 'something'
    ///                      else it must control with font forge the equality between family and font name
    /// \param piececolor  : the color of the piece  clicked
    /// \param rank        : the rank A B C ... H of the piece clicked
    /// \param file        : the file 1 2 3 ... 8 of the piece cliecked
    /// \param side        : Color WHITE or BLACK
    /// \param ptr         : a pointer  on the chess board
    /// \return 
    ///
    static QCursor getCursor(int widthtile, int heighttile, QString font, QColor color, int rank,int file, Color side, ChessBoard *ptr);
};

#endif // CHESBOARDCURSOR_H
