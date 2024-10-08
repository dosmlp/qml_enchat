#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQmlContext>
#include "friendlistmodel.h"
#include "chathistory.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    // QQuickWindow::setGraphicsApi(QSGRendererInterface::Software);
    QQmlApplicationEngine engine;

    FriendListModel model;
    engine.rootContext()->setContextProperty("friendListModel",&model);
    ChatHistory::Model chathis;
    engine.rootContext()->setContextProperty("chatRecordModel",&chathis);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("qml_enchat", "Main");

    return app.exec();
}
