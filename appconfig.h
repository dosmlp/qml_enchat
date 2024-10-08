#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QObject>
#include <QJsonDocument>

class AppConfig : public QObject
{
    Q_OBJECT
public:
    static AppConfig* instance()
    {
        Q_ASSERT(self_ == nullptr);
        self_ = new AppConfig();
    }
signals:
private:
    explicit AppConfig(QObject *parent = nullptr);
    static AppConfig* self_;
};

#endif // APPCONFIG_H
