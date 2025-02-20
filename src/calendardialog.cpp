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

#include "calendardialog.h"
#include <QHBoxLayout>

CalendarDialog::CalendarDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Select a date or current date :"));

    QVBoxLayout *layout = new QVBoxLayout(this);
    calendarWidget = new QCalendarWidget(this);
    abortButton= new QPushButton(this);
    abortButton->setText(tr("Abort"));
    layout->addWidget(calendarWidget);
    layout->addWidget(abortButton);
    connect(calendarWidget, &QCalendarWidget::clicked, this, &CalendarDialog::accept);
    connect(abortButton, &QPushButton::clicked, this, &CalendarDialog::reject);
}


QDate CalendarDialog::selectedDate() const
{
    return calendarWidget->selectedDate();
}

bool CalendarDialog::status() {return mResult;}

void CalendarDialog::accept() {mResult=true;done(Accepted);}
void CalendarDialog::reject() {mResult=false;done(Rejected); }

