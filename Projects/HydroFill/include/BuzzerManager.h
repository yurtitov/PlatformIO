#pragma once

#include <Arduino.h>

#define BUZZER_PIN 2

class BuzzerManager {
public:
    BuzzerManager();
    void begin();
    void on();
    void off();

private:
    int _pin;
};