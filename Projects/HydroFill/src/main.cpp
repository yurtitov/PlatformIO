#include <Arduino.h>
#include <WiFiManager.h>
#include <TimeManager.h>
#include <ConfigManager.h>
#include <PressureSensor.h>
#include <Display_1_77_TFT_Manager.h>
#include <TemperatureSensor.h>

#define LED_ERROR_PIN 39
#define LED_POWER_ON_PIN 40
#define LED_SOLENOID_VALVE_OPEN_PIN 38

#define BUZZER_PIN 2
#define SOLENOID_VALVE_PIN 1

ConfigData cfg;
WiFi_Manager *wifi = nullptr;
TimeManager *timeService = nullptr;
PressureSensor pressureSensor(0.2f);
TemperatureSensor temperatureSensor;

// Функция-обертка для задачи FreeRTOS
void pressureTask(void *pvParameters)
{
  while (true)
  {
    pressureSensor.update();                // Опрашиваем датчик (это занимает ~750мс из-за delay)
    vTaskDelay(pdMS_TO_TICKS(100)); // Небольшая пауза между циклами опроса
  }
}

void temperatureTask(void *pvParameters)
{
  while ( true)
  {
    temperatureSensor.update();
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

Display_1_77_TFT_Manager display;

void setup()
{
  display.begin();

  Serial.begin(115200);
  delay(2000);

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

  pressureSensor.begin();
  xTaskCreate(
      pressureTask,   // Функция задачи
      "PressureTask", // Имя задачи
      4096,           // Размер стека
      NULL,           // Параметры
      1,              // Приоритет
      NULL            // Хендл задачи
  );

  temperatureSensor.begin();
  xTaskCreate(
    temperatureTask,
    "TemperatureTask",
    4096,
    NULL,
    1,
    NULL
  );

  pinMode(LED_POWER_ON_PIN, OUTPUT);
  digitalWrite(LED_POWER_ON_PIN, LOW);

  pinMode(LED_ERROR_PIN, OUTPUT);
  digitalWrite(LED_ERROR_PIN, LOW);

  pinMode(LED_SOLENOID_VALVE_OPEN_PIN, OUTPUT);
  digitalWrite(LED_SOLENOID_VALVE_OPEN_PIN, LOW);

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  pinMode(SOLENOID_VALVE_PIN, OUTPUT);
  digitalWrite(SOLENOID_VALVE_PIN, LOW);

  display.clean();
}

void loop()
{
  float pressure = pressureSensor.getLatestPressure();

  float temperature = temperatureSensor.getTemperature();
  if (!temperatureSensor.isSensorConnected()) {
    Serial.println("Error: Temperature sensor not found");
  }

  // String time = timeService->getFormattedTime("%H:%M");

  digitalWrite(LED_ERROR_PIN, HIGH);

  // digitalWrite(LED_POWER_ON_PIN, HIGH);
  // digitalWrite(LED_SOLENOID_VALVE_OPEN_PIN, HIGH);
  // digitalWrite(SOLENOID_VALVE_PIN, HIGH);

  display.printInfo(temperature, pressure);

  // digitalWrite(SOLENOID_VALVE_PIN, LOW);
  // digitalWrite(LED_SOLENOID_VALVE_OPEN_PIN, LOW);
  delay(100);
  
}
