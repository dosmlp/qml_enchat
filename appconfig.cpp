#include "appconfig.h"

uint8_t AppConfig::private_key[64] = {0};
uint8_t AppConfig::public_key[32] = {0};
AppConfig* AppConfig::self_ = nullptr;
