#pragma once

#include <Arduino.h>

#define LED_RED_PIN 39
#define LED_GREEN_PIN 40
#define LED_BLUE_PIN 38

class LED {
public:
    LED(int pin);
    void begin();
    void on();
    void off();
    void toggle();

private:
    int _pin;
};

class LEDSignalManager {
public:
    LEDSignalManager();
    void begin();
    void showDemo();
    void showMonitoring();
    void showRefilling();
    void showAlarm();

private:
    LED _ledGreen;
    LED _ledRed;
    LED _ledBlue;
    void onAll();
    void offAll();
};