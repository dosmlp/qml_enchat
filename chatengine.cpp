#include "chatengine.h"
#include "friendlistmodel.h"
#include "chathistory.h"
#include <QQmlContext>
#include <QDebug>

ChatEngine::ChatEngine(QObject *parent)
    : QObject{parent},
    client_(new ChatClient(this,"test")),
    server_(new ChatServer(10334,this))
{
    connect(client_,&ChatClient::sigClose,this,&ChatEngine::onClose,Qt::QueuedConnection);
    connect(client_,&ChatClient::sigConnected,this,&ChatEngine::onConnected,Qt::QueuedConnection);
    connect(client_,&ChatClient::sigHandshakeFinished,this,&ChatEngine::onHandShakeFinished,Qt::QueuedConnection);
    connect(client_,&ChatClient::sigTextMsg,this,&ChatEngine::onTextMsg,Qt::QueuedConnection);
    connect(server_,&ChatServer::sigClose,this,&ChatEngine::onClose,Qt::QueuedConnection);
    connect(server_,&ChatServer::sigConnected,this,&ChatEngine::onConnected,Qt::QueuedConnection);
    connect(server_,&ChatServer::sigHandshakeFinished,this,&ChatEngine::onHandShakeFinished,Qt::QueuedConnection);
    connect(server_,&ChatServer::sigTextMsg,this,&ChatEngine::onTextMsg,Qt::QueuedConnection);
}

void ChatEngine::sendText(QString id, const QString &text)
{
    if (id.isEmpty()) return;

    if (!chat_history_) {
        QObject* var = qml_engine_->rootContext()->objectForName("chatHistoryModel");
        chat_history_ = qobject_cast<ChatHistoryModel*>(var);
    }
    chat_history_->add(text,id);
    client_->sendTextMsg(id,text);
}

void ChatEngine::connectToPeer(const QString &id)
{
    if (!peers_model_) {
        QObject* var = qml_engine_->rootContext()->objectForName("friendListModel");
        peers_model_ = qobject_cast<FriendList::Model*>(var);
    }
    Peer::Ptr peer = peers_model_->getPeer(id);
    client_->doConnect(peer->address.toStdString(),
                       peer->port,
                       peer->pub_key);
}

void ChatEngine::onConnected(const QString& id)
{
    SINFO("connected:{}",id);
}

void ChatEngine::onTextMsg(const QString& id, const QString &text)
{
    if (!chat_history_) {
        QObject* var = qml_engine_->rootContext()->objectForName("ChatHistoryModel");
        chat_history_ = qobject_cast<ChatHistoryModel*>(var);
    }
    chat_history_->add(text);
}

void ChatEngine::onClose(const QString& id)
{
    SINFO("close:{}",id);
}

void ChatEngine::onHandShakeFinished(const QString& id)
{
    SINFO("HandShakeFinished:{}",id);
}
