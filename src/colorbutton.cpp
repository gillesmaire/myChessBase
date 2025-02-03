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
#include "colorbutton.h"

#include <QColorDialog>
#include <QSettings>
#include <QColorDialog>

ColorButton::ColorButton(QWidget *parent):QPushButton(parent)
{
    connect (this,&ColorButton::clicked,this,&ColorButton::ButtondefineColor);
}

void ColorButton::setName(QString name)
{
    mButtonName=name;
    QSettings s;
    mColor=QColor(s.value(name).toString());
}


void ColorButton::paintEvent(QPaintEvent *)
{   
    QPainter p(this);
    if (!p.isActive()) { qWarning("QPainter is not active (26)!"); return ;}

    p.setBrush(mColor);
    p.setPen(mColor);
    p.drawRect(0,0,width(),height());
}

void ColorButton::ButtondefineColor()
{       QColorDialog *dialog = new QColorDialog(this);
        dialog->setCustomColor(0,mColor);
        dialog->setOption(QColorDialog::DontUseNativeDialog);
        dialog->show();
        connect(dialog,&QColorDialog::accepted,[=](){
            mColor=dialog->currentColor();
            emit ColorChanged(mButtonName,mColor);
        }
        );
}


