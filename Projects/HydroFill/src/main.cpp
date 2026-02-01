#include <Arduino.h>
#include <WiFiManager.h>
#include <TimeManager.h>
#include <ConfigManager.h>

ConfigData cfg;
WiFi_Manager *wifi = nullptr;
TimeManager *timeService = nullptr;

void setup()
{
  Serial.begin(115200);
  delay(2000);

  if (ConfigManager::load(cfg))
  {
    WiFi_Manager wifi(cfg.ssid.c_str(), cfg.pass.c_str());
    TimeManager timeService(cfg.ntp_server.c_str(), cfg.gmt_offset, 0);

    wifi.connect();
    timeService.begin();

    Serial.println("[System] Ready with config from LittleFS");
  }
  else
  {
    Serial.println("[ERROR] Config load failed!");
  }
}

void loop()
{
  if (wifi != nullptr && timeService != nullptr)
  {
    if (wifi->isConnected())
    {
      Serial.print("[DATA] " + timeService->getFormattedTime());
      Serial.print(" | ");
      wifi->printSignalQuality();
    }
    else
    {
      Serial.println("[System] Waiting for WiFi...");
    }
  }
  delay(5000);
}
