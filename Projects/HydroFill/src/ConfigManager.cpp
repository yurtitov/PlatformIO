#include <ConfigManager.h>

bool ConfigManager::load(ConfigData &config)
{
    if (!LittleFS.begin(true))
    {
        Serial.println("[Config] LittleFS Mount Failed");
        return false;
    }

    File file = LittleFS.open("/config.json", "r");
    if (!file)
    {
        Serial.println("[Config] Failed to open file");
        return false;
    }

    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, file);
    file.close();

    if (error)
    {
        Serial.println("[Config] JSON Parse Failed");
        return false;
    }

    config.ssid = doc["wifi_ssid"] | "";
    config.pass = doc["wifi_pass"] | "";
    config.ntp_server = doc["ntp_server"] | "pool.ntp.org";
    config.gmt_offset = doc["gmt_offset"] | 0;

    return true;
}
