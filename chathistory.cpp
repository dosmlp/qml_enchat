#include "chathistory.h"
namespace ChatHistory {
Model::Model(QObject *parent)
    : QAbstractListModel(parent)
{
    history_.reserve(4096);

    for (int i = 0;i < 100;++i)
    {
        Node::Ptr p = std::make_shared<Node>();
        p->author = "Mes";
        p->message = "asdhio厚爱的奥胖激发";
        p->recipient = "Me";
        p->time = QDateTime::currentDateTime();
        history_.append(p);
    }
}

int Model::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return history_.size();
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    int row = index.row();
    if (row > history_.size())
        return QVariant();

    switch (role)
    {
    case Roles::author:
        return history_.at(row)->author;
    case Roles::recipient:
        return history_.at(row)->recipient;
    case Roles::message:
        return history_.at(row)->message;
    case Roles::time:
        return history_.at(row)->time;
    }

    return QVariant();
}

QMap<int, QVariant> Model::itemData(const QModelIndex &index) const
{
    int row = index.row();

    Node::Ptr p = history_.at(row);

    QMap<int,QVariant> map;
    map.insert(Roles::author,p->author);
    map.insert(Roles::recipient,p->recipient);
    map.insert(Roles::message,p->message);
    map.insert(Roles::time,p->time);
    return map;
}

bool Model::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
    return true;
}

bool Model::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
    return true;
}
}
