#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QVariantMap>

extern "C" {
#include <mbedtls/base64.h>
#include "boringssl/curve25519.h"
}
#include "xlog.h"
#include "qjson_helper.h"
#include "Peer.h"

using namespace nlohmann;

class AppConfig
{
public:
    static bool containsPeerPubkey(const QByteArray& key)
    {
        if (self_) {
            return self_->_containsPeerPubkey(key);
        }
        return false;
    }
    static void parse(const QString& file)
    {
        if (self_) {
            self_->_parse(file);
        }

    }
    static QList<Peer::Ptr> getPeerList()
    {
        return self_->_getPeerList();
    }
    static void parse2(const std::string& file)
    {
        std::ifstream cfg_file(file);
        json root = json::parse(cfg_file,nullptr,false);
        if (root.is_discarded() || root.empty()) {
            SERROR("cfg error!");
            return;
        }
        auto private_key = root.at("private_key").get<std::string>();//root.value("private_key","");
        std::string pub_key = root.value("public_key","");
        size_t outlen = 0;

        mbedtls_base64_decode(AppConfig::private_key, 64, &outlen, (const uint8_t*)private_key.data(), private_key.length());
        mbedtls_base64_decode(AppConfig::public_key, 32, &outlen, (const uint8_t*)pub_key.data(), pub_key.length());
    }
    //生成ed25519签名密钥对
    static void ed25519()
    {
        uint8_t public_key[32] = {0};
        uint8_t private_key[64] = {0};
        ED25519_keypair(public_key, private_key);

        uint8_t out_base64[128] = {0};
        size_t olen = 0;
        mbedtls_base64_encode(out_base64, 128, &olen, public_key, 32);
        std::cout << "----------public_key----------\n";
        for (int i = 0;i < 32;++i) {
            std::cout << std::hex << (uint32_t)(public_key[i]);
        }
        std::cout << "\n";
        std::cout << out_base64 << "\n";

        memset(out_base64, 0, 128);
        mbedtls_base64_encode(out_base64, 128, &olen, private_key, 64);
        std::cout << "----------private_key----------\n";
        for (int i = 0;i < 64;++i) {
            std::cout << std::hex << (uint32_t)(private_key[i]);
        }
        std::cout << "\n";
        std::cout << out_base64 << "\n";
    }

    //toJson fromJson

    void fromJson(const QJsonValue& j)
    {
        if (const QJsonValue& v = j["private_key"]; v.isString()) {
            pri_key = QByteArray::fromBase64(v.toString().toLatin1());
        }
        if (const QJsonValue& v = j["public_key"]; v.isString()) {
            pub_key = QByteArray::fromBase64(v.toString().toLatin1());
        }
        if (const QJsonValue& v = j["server_port"]; v.isDouble()) {
            server_port = v.toInt();
        }
        if (const QJsonValue& v = j["peers"]; v.isArray()) {
            QJsonHelper::get<QList<Peer::Ptr>>(v,peers_);
        }
        memcpy(public_key,pub_key.data(),32);
        memcpy(private_key,pri_key.data(),64);
    }
    QJsonValue toJson()
    {
        QJsonObject o;
        o["private_key"] = QString(pri_key.toBase64());
        o["public_key"] = QString(pub_key.toBase64());
        o["server_port"] = server_port;
        o["peers"] = QJsonHelper::to<QList<Peer::Ptr>>(peers_);
        return o;
    }

    static void init()
    {
        self_ = new AppConfig;
        self_->_parse("cfg.json");
    }
    static AppConfig* instance()
    {
        return self_;
    }
    static void release()
    {
        delete self_;
        self_ = nullptr;
    }
    static uint8_t public_key[32];
    static uint8_t private_key[64];
private:
    static AppConfig* self_;
    QByteArray pub_key;
    QByteArray pri_key;
    uint16_t server_port;
    QList<Peer::Ptr> peers_;

    bool _containsPeerPubkey(const QByteArray& key)
    {
        for (const Peer::Ptr& p:peers_) {
            if (p->pub_key == key) {
                return true;
            }
        }
        return false;
    }
    void _parse(const QString& file)
    {
        QFile file_cfg(file);
        if (!file_cfg.open(QIODevice::ReadOnly)) {
            SERROR("open cfg fail.");
            return;
        }
        QJsonParseError parse_error;
        QJsonDocument doc = QJsonDocument::fromJson(file_cfg.readAll(), &parse_error);
        if (doc.isEmpty() || doc.isNull() || parse_error.error != QJsonParseError::NoError) {
            SERROR("parse cfg json error.");
            return;
        }

        QJsonObject obj_root = doc.object();
        QJsonHelper::get<AppConfig>(obj_root,*this);
    }

    QList<Peer::Ptr> _getPeerList() const
    {
        return peers_;
    }
};

