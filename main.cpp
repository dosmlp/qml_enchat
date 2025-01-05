#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQmlContext>
#include <QLoggingCategory>
#include <QQuickGraphicsConfiguration>
#include <QDebug>
#include <asio.hpp>
#include "friendlistmodel.h"
#include "chathistory.h"
#include "appconfig.h"
#include "xlog.h"
#include "mbedtls.h"
#include "exceptiondump.h"
#include "chatclient.h"

#include <ylt/struct_pack.hpp>
#include <stdint.h>
#include <QWKQuick/qwkquickglobal.h>
#pragma comment( linker, "/subsystem:console /entry:WinMainCRTStartup" )
#if 1
// 1. sp_get_needed_size: 预计算序列化长度
std::size_t sp_get_needed_size(const QString& qstr) {
    return sizeof(uint32_t)+sizeof(QChar)*qstr.size();
}
// 2. sp_serialize_to: 将对象序列化到writer
template <typename Writer>
void sp_serialize_to(Writer& writer, const QString& qstr) {
    uint32_t size = sizeof(QChar)*qstr.size();
    struct_pack::write(writer, size);
    struct_pack::write(writer, (char*)qstr.unicode(), size);
}
// 3. sp_deserialize_to: 从reader反序列化对象
template <typename Reader>
struct_pack::err_code sp_deserialize_to(Reader& reader, QString& qstr) {
    uint32_t size;
    struct_pack::read(reader,size);
    qstr.resize(size/sizeof(QChar));
    return struct_pack::read(reader, (char*)qstr.data(), size);
}
#endif
int main(int argc, char *argv[])
{
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
    ExceptionDump::Init("./");
    XLogMgr::get()->InitLog("./","qml_enchat","qml_enchat");
    init_mbedtls();

    QGuiApplication app(argc, argv);
    QQuickGraphicsConfiguration config;
    config.setDebugLayer(true);
    config.setDebugMarkers(true);
    // QQuickWindow::setGraphicsApi(QSGRendererInterface::Software);
    QQuickWindow::setTextRenderType(QQuickWindow::NativeTextRendering);
    // QQuickWindow::setGraphicsConfiguration(config);
    AppConfig::init();
    QQmlApplicationEngine engine;
    QWK::registerTypes(&engine);
    // QLoggingCategory::setFilterRules(QStringLiteral("qt.qml.binding.removal.info=true"));

    FriendList::Model model;
    engine.rootContext()->setContextProperty("friendListModel",&model);
    ChatHistoryModel* history = ChatHistoryModel::create(nullptr,nullptr);
    engine.rootContext()->setContextProperty("chatHistoryModel",history);


    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("qml_enchat", "Main");

    // auto list = engine.rootObjects();
    // QQuickWindow* window = qobject_cast<QQuickWindow*>(list.first());
    // if (window) {
    //     window->setGraphicsConfiguration(config);
    // }
    return app.exec();
}
