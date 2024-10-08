#ifndef FRIENDLISTMODEL_H
#define FRIENDLISTMODEL_H

#include <QAbstractListModel>

namespace FriendList {
struct Node {
    typedef std::shared_ptr<Node> Ptr;
    QString name;
    QString pub_key;
};

class Model : public QAbstractListModel
{
    Q_OBJECT

public:
    enum FriendListRoles {
        name = Qt::UserRole + 1,
        pub_key
    };
    explicit Model(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // Fetch data dynamically:
    bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;

    bool canFetchMore(const QModelIndex &parent) const override;
    void fetchMore(const QModelIndex &parent) override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    QHash<int,QByteArray> roleNames() const
    {
        QHash<int,QByteArray> roles;
        roles.insert(FriendListRoles::name,"name");
        roles.insert(FriendListRoles::pub_key,"pub_key");
        return roles;
    }

private:
    QList<Node::Ptr> friend_list_;
};
}
#endif // FRIENDLISTMODEL_H
