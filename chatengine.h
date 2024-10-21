#ifndef CHATENGINE_H
#define CHATENGINE_H

#include <QObject>
#include <QQmlEngine>

class ChatEngine : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
public:
    explicit ChatEngine(QObject *parent = nullptr);

    Q_INVOKABLE void sendText(uint64_t id, const QString& text);
signals:
};

#endif // CHATENGINE_H
