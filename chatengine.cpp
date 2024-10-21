#include "chatengine.h"
#include <QDebug>

ChatEngine::ChatEngine(QObject *parent)
    : QObject{parent}
{}

void ChatEngine::sendText(uint64_t id, const QString &text)
{

}
