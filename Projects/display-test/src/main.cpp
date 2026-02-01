#include <Arduino.h>
#include <U8g2lib.h>

// Используем SW_I2C, так как он показал стабильную работу на вашем модуле
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/9, /* data=*/8, /* reset=*/U8X8_PIN_NONE);

int counter = 0;

#define LED_PIN 17

void setup()
{
  // Wire.begin больше не нужен для Software I2C
  u8g2.begin();
  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop()
{
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));

  u8g2.clearBuffer(); // Очистка памяти дисплея

  // Настройка шрифта
  u8g2.setFont(u8g2_font_ncenB08_tr);

  // Вывод статического текста
  u8g2.drawStr(0, 12, "ESP32-S3 Counter:");

  // Вывод переменной counter
  u8g2.setCursor(0, 35); // Устанавливаем курсор (x, y)
  u8g2.setFont(u8g2_font_pcsenior_8f);
  u8g2.print("Count: ");
  u8g2.setFont(u8g2_font_logisoso16_tf);
  u8g2.print(counter); // Выводим само значение

  // Рисуем рамку вокруг счетчика для красоты
  u8g2.drawFrame(0, 42, 128, 20);

  // Рисуем полосу прогресса, которая зависит от счетчика
  u8g2.drawBox(0, 45, (counter % 128), 14);

  u8g2.sendBuffer(); // Физический вывод на экран

  counter++;  // Увеличиваем счетчик
  delay(100); // Обновление 10 раз в секунду (для плавности)
}
