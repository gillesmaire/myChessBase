#ifndef MYTABLEVIEW_H
#define MYTABLEVIEW_H

#include <QTableView>

class MyTableView : public QTableView
{
Q_OBJECT

public:
    MyTableView(QWidget *parent );
private:

void currentChanged(const QModelIndex &current, const QModelIndex &previous);

signals:
    void currentChangedSignal(QModelIndex, QModelIndex);
};


#endif // MYTABLEVIEW_H
