#include "mytableview.h"


MyTableView::MyTableView(QWidget *parent ):QTableView(parent)
{}

void MyTableView::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    emit currentChangedSignal(current, previous);
}
