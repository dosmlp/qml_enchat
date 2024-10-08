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
    explicit Model(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

private:
    QList<Node::Ptr> history_;
};
}



#endif // CHATHISTORY_H
