#pragma once
#include <ArduinoJson.h>
#include <LittleFS.h>

struct ConfigData
{
    String ssid;
    String pass;
    String ntp_server;
    long gmt_offset;
};

class ConfigManager
{
public:
    static bool load(ConfigData &config);
};