#include <Arduino.h>
#include <led.h>

#define DELAY_SHORT 100
#define DELAY_LONG 500
#define DELAY_LONG_LONG 2000

Led blueLed(21);

void setup()
{
  Serial.begin(115200);
  blueLed.init();
  pinMode(0, INPUT_PULLUP);
}

void loop()
{
  if (digitalRead(0) == LOW)
  {
    blueLed.on();
    delay(1);
    blueLed.off();
  }
  delay(50);
}