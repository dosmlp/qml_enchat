#ifndef CHATENGINE_H
#define CHATENGINE_H

#include <QObject>
#include <QQmlEngine>
#include "chatclient.h"
#include "chatserver.h"
#include "chatcallback.h"

class ChatEngine : public ChatCallBack
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
public:
    explicit ChatEngine(QObject *parent = nullptr);

    Q_INVOKABLE void sendText(QString id, const QString& text);

    void onConnected(const uint64_t id) override;
    void onTextMsg(const uint64_t id, const QString &text) override;
    void onClose(const uint64_t id) override;
    void onHandShakeFinished(const uint64_t id) override;

signals:
};

#endif // CHATENGINE_H
