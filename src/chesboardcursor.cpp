#include "chesboardcursor.h"
#include <QPixmap>


QCursor ChesBoardCursor::SetChessBoardCursor()
{
    QPixmap pm (QString(":/System/cursor.png"));
    QCursor cursor(pm);
    return cursor;
}
