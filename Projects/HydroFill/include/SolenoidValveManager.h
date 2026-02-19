#pragma once

#include <Arduino.h>

#define SOLENOID_VALVE_PIN 1

class SolenoidValveManager
{
public:
    SolenoidValveManager();
    void begin();
    void on();
    void off();
private:
    int _pin;
};
