#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQmlContext>
#include <QLoggingCategory>
#include <QDebug>
#include "friendlistmodel.h"
#include "chathistory.h"
#include "appconfig.h"
#include "xlog.h"
#include "mbedtls.h"
#include "exceptiondump.h"

int main(int argc, char *argv[])
{
    ExceptionDump::Init("./");
    XLogMgr::get()->InitLog("./","qml_enchat","qml_enchat");
    init_mbedtls();

    QGuiApplication app(argc, argv);
    QQuickWindow::setGraphicsApi(QSGRendererInterface::Software);
    QQuickWindow::setTextRenderType(QQuickWindow::NativeTextRendering);
    AppConfig::init();
    QQmlApplicationEngine engine;
    // QLoggingCategory::setFilterRules(QStringLiteral("qt.qml.binding.removal.info=true"));

    FriendList::Model model;
    engine.rootContext()->setContextProperty("friendListModel",&model);
    // ChatHistory::Model chathis;
    // engine.rootContext()->setContextProperty("chatRecordModel",&chathis);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("qml_enchat", "Main");

    return app.exec();
}
