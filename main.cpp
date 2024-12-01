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
#include "chatclient.h"

#include <ylt/struct_pack.hpp>
#include <stdint.h>
struct MSGG
{
    QString name;
    std::string pub_key;
    uint64_t id;
};
STRUCT_PACK_REFL(MSGG,name,pub_key,id)

// 1. sp_get_needed_size: 预计算序列化长度
std::size_t sp_get_needed_size(const QString& qstr) {
    return sizeof(uint32_t)+sizeof(QChar)*qstr.size();
}
// 2. sp_serialize_to: 将对象序列化到writer
template </*struct_pack::writer_t*/ typename Writer>
void sp_serialize_to(Writer& writer, const QString& qstr) {
    uint32_t size = sizeof(QChar)*qstr.size();
    struct_pack::write(writer, size);
    struct_pack::write(writer, (char*)qstr.unicode(), size);
}
// 3. sp_deserialize_to: 从reader反序列化对象
template </*struct_pack::reader_t*/ typename Reader>
struct_pack::err_code sp_deserialize_to(Reader& reader, QString& qstr) {
    uint32_t size;
    struct_pack::read(reader,size);
    qstr.resize(size/sizeof(QChar));
    return struct_pack::read(reader, (char*)qstr.data(), size);
}


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


    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("qml_enchat", "Main");


    return app.exec();
}
