// GPL 3.0 License
// Copyright (c)2025 Gilles Maire <gilles@gillesmaire.com>
// Project : %PROJECTNAME%
// Filename : formressources.cpp
// Creation date : 15/02/2025
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
// Source: %GITLOCATION%
//

#include "formresources.h"
#include "ui_formresources.h"
#include <QFileDialog>
#include <QSettings>
#include <QDir>
#include "myvisitor.h"

#include "chess.hpp"



FormResources::FormResources(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormResources)
{   
   ui->setupUi(this);
   connect(ui->pushButtonOpen,SIGNAL(clicked()),this,SLOT(SelectFile()));
}

FormResources::~FormResources()
{
    delete ui;
}


void FormResources::SelectFile()
{
    QSettings s;
    QString dir=s.value("DefaultDir",QDir::homePath()).toString();
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open PGN si4 or si5 file")
                        ,dir, tr("Chess file (*.pgn *.si5 *.si4)"));
    qDebug()<<fileName;
    if (! fileName.isNull()) {
        QFileInfo fi(fileName);
        s.setValue("DefaultDir",fi.absoluteDir().absolutePath());
        if ( fileName.toLower().endsWith(".pgn")) ReadPGN(fileName);
        else if (fileName.toLower().endsWith(".si4")) ReadSI4(fileName);
        else if (fileName.toLower().endsWith(".si5")) ReadSI5(fileName);
    }
}

void FormResources::ReadPGN( QString filename)
{
    Q_UNUSED(filename)
}

void FormResources::ReadSI4( QString filename)
{
    Q_UNUSED(filename)
}

void FormResources::ReadSI5( QString filename)
{
    Q_UNUSED(filename)
}

