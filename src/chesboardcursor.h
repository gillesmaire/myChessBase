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
