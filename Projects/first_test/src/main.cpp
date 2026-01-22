#include <Arduino.h>
#include <Wire.h>

#define I2C_SDA 8
#define I2C_SCL 9
#define SENSOR_ADDR 0x78

const float MAX_BAR = 10.0;
const int RAW_ZERO = 6678; // Уточненный ноль по вашим логам
const int RAW_RANGE = 13107;

void setup()
{
  Serial.begin(115200);
  Wire.begin(I2C_SDA, I2C_SCL);
  delay(500);
  Serial.println("Датчик готов к работе в системе отопления.");
}

void loop()
{
  long raw_sum = 0;
  int samples = 5;

  // Считываем 5 значений для стабильности
  for (int i = 0; i < samples; i++)
  {
    Wire.beginTransmission(SENSOR_ADDR);
    Wire.write(0xAC);
    Wire.endTransmission();
    delay(100);

    Wire.requestFrom(SENSOR_ADDR, 3);
    if (Wire.available() == 3)
    {
      Wire.read(); // Пропускаем статус
      byte msb = Wire.read();
      byte lsb = Wire.read();
      raw_sum += (msb << 8) | lsb;
    }
    delay(50);
  }

  int raw_avg = raw_sum / samples;

  // Расчет
  float pressure_bar = ((float)(raw_avg - RAW_ZERO) / RAW_RANGE) * MAX_BAR;
  if (pressure_bar < 0)
    pressure_bar = 0;

  // Вывод данных
  Serial.print("Давление в системе: ");
  Serial.print(pressure_bar, 2);
  Serial.print(" Bar");

  // Умные уведомления
  if (pressure_bar < 0.6)
  {
    Serial.println(" [ АВАРИЯ: ПУСТАЯ СИСТЕМА ]");
  }
  else if (pressure_bar < 1.2)
  {
    Serial.println(" [ ПРЕДУПРЕЖДЕНИЕ: НИЗКОЕ ДАВЛЕНИЕ ]");
  }
  else if (pressure_bar >= 1.2 && pressure_bar <= 2.2)
  {
    Serial.println(" [ НОРМА ]");
  }
  else
  {
    Serial.println(" [ ВНИМАНИЕ: ВЫСОКОЕ ДАВЛЕНИЕ ]");
  }

  delay(1000); // Обновляем раз в 1 секунду
}
