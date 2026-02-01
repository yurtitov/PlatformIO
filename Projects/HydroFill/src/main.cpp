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

PressureSensor sensor(PRESSURE_SENSOR_ADDR, I2C_SDA, I2C_SCL, 0.2f);

// Функция-обертка для задачи FreeRTOS
void pressureTask(void *pvParameters)
{
  Serial.println("[Task] Pressure sensor task started on Core " + String(xPortGetCoreID()));

  while (true)
  {
    sensor.update();                // Опрашиваем датчик (это занимает ~750мс из-за delay)
    vTaskDelay(pdMS_TO_TICKS(100)); // Небольшая пауза между циклами опроса
  }
}

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

  sensor.begin();
  xTaskCreate(
      pressureTask,   // Функция задачи
      "PressureTask", // Имя задачи
      4096,           // Размер стека
      NULL,           // Параметры
      1,              // Приоритет
      NULL            // Хендл задачи
  );
}

void loop()
{
  float p = sensor.getLatestPressure();
  PressureStatus st = sensor.getStatus();

  Serial.printf("Давление: %.2f Bar [%s]\n", p, sensor.getStatusString(st).c_str());

  delay(100);
}
