#include "chatengine.h"
#include <QDebug>

ChatEngine::ChatEngine(QObject *parent)
    : ChatCallBack{parent}
{}

void ChatEngine::sendText(QString id, const QString &text)
{
    qDebug()<<id<<999;
}

void ChatEngine::onConnected(const uint64_t id)
{

}

void ChatEngine::onTextMsg(const uint64_t id, const QString &text)
{

}

void ChatEngine::onClose(const uint64_t id)
{

}

void ChatEngine::onHandShakeFinished(const uint64_t id)
{

}
