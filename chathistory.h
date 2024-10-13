#ifndef CHATHISTORY_H
#define CHATHISTORY_H

#include <QAbstractListModel>
#include <QDateTime>

namespace ChatHistory {

struct Node {
    typedef std::shared_ptr<Node> Ptr;
    QString author;
    QString recipient;
    QString message;
    QDateTime time;

};

class Model : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        author = Qt::UserRole + 1,
        recipient,
        message,
        time
    };
    explicit Model(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QMap<int,QVariant> itemData(const QModelIndex &index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    QHash<int,QByteArray> roleNames() const
    {
        QHash<int,QByteArray> roles;
        roles.insert(Roles::author,"author");
        roles.insert(Roles::recipient,"recipient");
        roles.insert(Roles::message,"message");
        roles.insert(Roles::time,"time");
        return roles;
    }
private:
    QList<Node::Ptr> history_;
};
}



#endif // CHATHISTORY_H
