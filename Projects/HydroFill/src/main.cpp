#include <Arduino.h>
#include <WiFiManager.h>
#include <TimeManager.h>
#include <ConfigManager.h>
#include <PressureSensor.h>

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#define PRESSURE_SENSOR_ADDR 0x78
#define I2C_SDA 8
#define I2C_SCL 9

#define LED_ERROR_PIN 39
#define LED_POWER_ON_PIN 40
#define LED_SOLENOID_VALVE_OPEN_PIN 38

#define BUZZER_PIN 2
#define SOLENOID_VALVE_PIN 1

// DISPLAY_PIN_1_GND
// DISPLAY_PIN_2_VCC
#define DISPLAY_PIN_3_SCK 11
#define DISPLAY_PIN_4_SDA 10
#define DISPLAY_PIN_5_RES 7
#define DISPLAY_PIN_6_RS 6
#define DISPLAY_PIN_7_CS 5
// DISPLAY_PIN_8_LEDA

ConfigData cfg;
WiFi_Manager *wifi = nullptr;
TimeManager *timeService = nullptr;

PressureSensor sensor(PRESSURE_SENSOR_ADDR, I2C_SDA, I2C_SCL, 0.2f);

Adafruit_ST7735 display = Adafruit_ST7735(DISPLAY_PIN_7_CS, DISPLAY_PIN_6_RS, DISPLAY_PIN_4_SDA, DISPLAY_PIN_3_SCK, DISPLAY_PIN_5_RES);

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

int counter = 0;

void setup()
{
  Serial.begin(115200);
  delay(2000);

  // display.begin();
  // display.drawMessage("BOOTING...", "Connecting WiFi");

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

  // sensor.begin();
  // xTaskCreate(
  //     pressureTask,   // Функция задачи
  //     "PressureTask", // Имя задачи
  //     4096,           // Размер стека
  //     NULL,           // Параметры
  //     1,              // Приоритет
  //     NULL            // Хендл задачи
  // );

  display.initR(INITR_BLACKTAB);
  display.setRotation(1);
  display.fillScreen(ST77XX_BLACK);

  display.setCursor(10, 30);
  display.setTextColor(ST77XX_GREEN);
  display.setTextSize(3);
  display.println("YTTY");

  display.setCursor(10, 60);
  display.setTextColor(ST77XX_WHITE);
  display.setTextSize(2);
  display.println("Hello World!");

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
}

void loop()
{
  // float p = sensor.getLatestPressure();
  // String st = sensor.getStatusString(sensor.getStatus());
  // String time = timeService->getFormattedTime("%H:%M");

  // Serial.printf("Давление: %.2f Bar [%s]\n", p, st.c_str());

  // display.drawDashboard(p, st, time);

  // delay(100);

  digitalWrite(LED_POWER_ON_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_SOLENOID_VALVE_OPEN_PIN, HIGH);
  digitalWrite(SOLENOID_VALVE_PIN, HIGH);
  delay(2000);

  display.setCursor(10, 90);
  display.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  display.setTextSize(2);
  display.print("Counter ");
  display.println(++counter);
  
  digitalWrite(SOLENOID_VALVE_PIN, LOW);
  digitalWrite(LED_SOLENOID_VALVE_OPEN_PIN, LOW);
  delay(10000);
}
