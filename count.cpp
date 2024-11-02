#include "count.h"

Count::Count(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant Count::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex Count::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex Count::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int Count::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;
    
    // FIXME: Implement me!
}

int Count::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;
    
    // FIXME: Implement me!
}

QVariant Count::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    
    // FIXME: Implement me!
    return QVariant();
}
