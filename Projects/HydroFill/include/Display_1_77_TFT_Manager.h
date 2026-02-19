#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

// DISPLAY_PIN_1_GND
// DISPLAY_PIN_2_VCC
#define DISPLAY_PIN_3_SCK 11
#define DISPLAY_PIN_4_SDA 10
#define DISPLAY_PIN_5_RES 7
#define DISPLAY_PIN_6_RS 6
#define DISPLAY_PIN_7_CS 5
// DISPLAY_PIN_8_LEDA

class Display_1_77_TFT_Manager
{
public:
    Display_1_77_TFT_Manager();
    void begin();
    void clean();
    void printDemo();
    void printInfo(float temperature, float pressure);
    void printPumpingWater(int duration_millis, float pressure);
    void printAlarm(String cause);
    void printDebug(String msg);
private:
    Adafruit_ST7735 _display;
    void drawWarning(int16_t x, int16_t y, int16_t size);
};
