#ifndef CHATENGINE_H
#define CHATENGINE_H

#include <QObject>
#include <QQmlEngine>
#include "chatclient.h"
#include "chatserver.h"
#include "chatcallback.h"
#include "common.h"

namespace FriendList {
class Model;
}

class ChatHistoryModel;

class ChatEngine : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
public:

    ~ChatEngine()
    {}
    static ChatEngine *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
    {
        if (self_ == nullptr) self_ = new ChatEngine();
        self_->setQmlEngine(qmlEngine);
        // Create the object using some custom constructor or factory.
        // The QML engine will assume ownership and delete it, eventually.
        return self_;
    }

    Q_INVOKABLE void sendText(QString id, const QString& text);
    Q_INVOKABLE void connectToPeer(const QString& id);

    void onConnected(const QString& id);
    void onTextMsg(const QString& id, const QString &text);
    void onClose(const QString& id);
    void onHandShakeFinished(const QString& id);
    void setQmlEngine(QQmlEngine* e)
    {
        qml_engine_ = e;
    }
signals:
private:
    explicit ChatEngine(QObject *parent = nullptr);
    ChatClient* client_;
    ChatServer* server_;

    inline static ChatEngine* self_ = nullptr;
    QQmlEngine* qml_engine_ = nullptr;

    FriendList::Model* peers_model_ = nullptr;
    ChatHistoryModel* chat_history_ = nullptr;
};

#endif // CHATENGINE_H
