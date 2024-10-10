#include "friendlistmodel.h"
#include "appconfig.h"

namespace FriendList {
Model::Model(QObject *parent)
    : QAbstractListModel(parent)
{

    friend_list_ = AppConfig::getPeerList();

}

int Model::rowCount(const QModelIndex &parent) const
{

    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return friend_list_.size();
    // FIXME: Implement me!
}

bool Model::hasChildren(const QModelIndex &parent) const
{
    // FIXME: Implement me!
    return false;
}

bool Model::canFetchMore(const QModelIndex &parent) const
{
    // FIXME: Implement me!
    return false;
}

void Model::fetchMore(const QModelIndex &parent)
{
    // FIXME: Implement me!
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    int row = index.row();
    if (row < 0 || row > friend_list_.size()) {
        return QVariant();
    }

    switch (role) {
    case FriendListRoles::name:
        return friend_list_.at(row)->name;
        break;
    case FriendListRoles::pub_key:
        return friend_list_.at(row)->pub_key.toBase64();
        break;
    default:
        break;
    }
    // FIXME: Implement me!
    return QVariant();
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
