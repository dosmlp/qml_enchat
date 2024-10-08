#include "appconfig.h"

AppConfig* AppConfig::self_ = nullptr;

AppConfig::AppConfig(QObject *parent)
    : QObject{parent}
{}
