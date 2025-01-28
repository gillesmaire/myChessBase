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
#include "nag.h"
#include <QString>
#include <QObject>
#include <QRegularExpression>



QString Nag::getNagDescription(int nag) 
{
  return NagDescriptions.at(nag);
}

QStringList Nag::getNagList() 
{
   return NagDescriptions;
}

QStringList Nag::getNagListNumbered() 
{
 QStringList ret;
 int i=0;
 for ( auto e : NagDescriptions)
   ret<< QString("%1 - %2").arg(i++).arg(e);
 return ret;
}

QString Nag::getNag(QString linecombobox) 
{
   QStringList l= linecombobox.split(" - ");
   bool ok;
   int val=l.at(0).toInt(&ok);
   if (val ==  0) return QString();
   else if ( val == 1 )  return("!!");
   else if ( val == 2 )  return("??");
   else if ( val == 3 )  return("!");
   else if ( val == 4 )  return("?");
   else if ( val == 5 )  return("!?");
   else if ( val == 6 )  return("?!");
   else return( QString("#%1").arg(val));
}

bool Nag::isNag(QTextEdit *te) 
{ QTextCursor cursor = te->textCursor();
  cursor.select(QTextCursor::WordUnderCursor); 
  QString word = cursor.selectedText();
  QRegularExpression nagPattern(R"(^(\!\!|\!\?|\?\?|\?|\!|\?\!|\!?|\?!|#\d+|\# \d+)$)");
  return nagPattern.match(word).hasMatch();
}
