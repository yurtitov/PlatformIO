#include <Arduino.h>
#include <WiFiManager.h>
#include <TimeManager.h>
#include <ConfigManager.h>
#include <RefillSystem.h>

ConfigData cfg;
WiFi_Manager *wifi = nullptr;
TimeManager *timeService = nullptr;

RefillSystem refillSistem;

void setup()
{
  Serial.begin(115200);
  delay(2000);

  refillSistem.begin();

  // TimeManager timeService(cfg.ntp_server.c_str(), cfg.gmt_offset, 0);
  // timeService.begin();

  // if (ConfigManager::load(cfg))
  // {
  //   WiFi_Manager wifi(cfg.ssid.c_str(), cfg.pass.c_str());

  //   wifi.connect();

  //   Serial.println("[System] Ready with config from LittleFS");
  // }
  // else
  // {
  //   Serial.println("[ERROR] Config load failed!");
  // }
}

void loop()
{
  refillSistem.update();

  // float pressure = pressureSensor.getLatestPressure();

  // float temperature = temperatureSensor.getTemperature();
  // if (!temperatureSensor.isSensorConnected()) {
    // Serial.println("Error: Temperature sensor not found");
  // }

  // String time = timeService->getFormattedTime("%H:%M");
}
