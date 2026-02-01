#include <Arduino.h>
#include <WiFiManager.h>
#include <TimeManager.h>
#include <ConfigManager.h>
#include <PressureSensor.h>

#define PRESSURE_SENSOR_ADDR 0x78
#define I2C_SDA 8
#define I2C_SCL 9

ConfigData cfg;
WiFi_Manager *wifi = nullptr;
TimeManager *timeService = nullptr;
PressureSensor *sensor = nullptr;

void setup()
{
  Serial.begin(115200);
  delay(2000);

  sensor = new PressureSensor(PRESSURE_SENSOR_ADDR, I2C_SDA, I2C_SCL);
  sensor->begin();

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

  if (sensor != nullptr)
  {
    float p = sensor->readPressure();
    PressureStatus st = sensor->getStatus(p);

    // Красивый вывод в Serial
    Serial.printf("[%s] Давление: %.2f Bar | Статус: %s\n",
                  timeService ? timeService->getFormattedTime("%H:%M:%S").c_str() : "00:00:00",
                  p,
                  sensor->getStatusString(st).c_str());

    if (wifi && wifi->isConnected())
    {
      // Здесь в будущем можно отправить данные в облако/Telegram
    }
  }

  delay(100);
}
