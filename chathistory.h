#ifndef CHATHISTORY_H
#define CHATHISTORY_H

#include <QAbstractListModel>
#include <QDateTime>
#include <QQmlEngine>

struct ChatHistoryNode {
    typedef std::shared_ptr<ChatHistoryNode> Ptr;
    QString author;
    QString recipient;
    QString message;
    QDateTime time;

};

class ChatHistoryModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    enum Roles {
        author = Qt::UserRole + 1,
        recipient,
        message,
        time
    };

    static ChatHistoryModel *create(QQmlEngine *, QJSEngine *engine)
    {
        static ChatHistoryModel *result = new ChatHistoryModel;
        // Create the instance using some custom constructor or factory.
        // The QML engine will assume ownership and delete it, eventually.
        return result;
    }

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
    Q_INVOKABLE void add(const QString& msg,const QString& to = QString())
    {
        if (current_peer_.isEmpty()) return;

        beginInsertRows(QModelIndex(),history_.size(),history_.size());
        ChatHistoryNode::Ptr p = std::make_shared<ChatHistoryNode>();
        p->author = "Me";
        p->message = msg;
        p->recipient = to.isEmpty()?current_peer_:to;
        p->time = QDateTime::currentDateTime();
        history_.append(p);
        endInsertRows();
        emit dataChanged(createIndex(history_.size()-1,0),createIndex(history_.size()-1,0));
    }
    Q_INVOKABLE void changePeer(const QString& pk);
private:
    explicit ChatHistoryModel(QObject *parent = nullptr);

    QString current_peer_;
    QMap<QString,QList<ChatHistoryNode::Ptr>> historys_;
    QList<ChatHistoryNode::Ptr> history_;
};




#endif // CHATHISTORY_H
