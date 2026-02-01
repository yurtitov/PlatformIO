#include <Arduino.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>

// Настройки оборудования
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW // Если будет перевернуто, замените на GENERIC_HW
#define MAX_DEVICES 1

// Пины для ESP32-S3 (используем ваши текущие пины)
#define DATA_PIN 11
#define CLK_PIN 12
#define CS_PIN 10

MD_Parola display = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// Битмап большого сердца
const uint8_t heartBig[] = {
    0b00011100, 0b00111110, 0b01111111, 0b11111110, 0b11111110, 0b01111111, 0b00111110, 0b00011100};

// Битмап маленького сердца
const uint8_t heartSmall[] = {
    0b00000000, 0b00011000, 0b00111100, 0b01111000, 0b01111000, 0b00111100, 0b00011000, 0b00000000};

void drawHeart(const uint8_t *heartData)
{
  MD_MAX72XX *mx = display.getGraphicObject();
  for (int i = 0; i < 8; i++)
  {
    mx->setColumn(0, i, heartData[i]);
  }
}

void setup()
{
  display.begin();
  display.setIntensity(1); // Минимальная яркость, чтобы не было "квадратов" из-за питания
  display.displayClear();
}

void loop()
{
  // 1. Рисуем большое сердце
  drawHeart(heartBig);
  delay(500); // Пауза в спокойном состоянии

  // 2. Рисуем маленькое сердце (эффект сжатия)
  drawHeart(heartSmall);
  delay(150); // Короткая пауза для эффекта удара

  // 3. Снова большое сердце
  drawHeart(heartBig);
  delay(150);

  // 4. Маленькое сердце
  drawHeart(heartSmall);
  delay(600); // Пауза между ударами пульса
}
