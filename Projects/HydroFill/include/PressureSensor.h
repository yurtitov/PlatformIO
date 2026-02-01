#pragma once
#include <Arduino.h>
#include <Wire.h>

enum PressureStatus
{
    EMPTY_SYSTEM,
    LOW_PRESSURE,
    NORMAL_PRESSURE,
    HIGH_PRESSURE
};

class PressureSensor
{
private:
    uint8_t _addr;
    int _sda, _scl;

    const float MAX_BAR = 10.0;
    const int RAW_ZERO = 6678;
    const int RAW_RANGE = 13107;

public:
    PressureSensor(uint8_t addr, int sda, int scl);
    void begin();
    float readPressure();
    PressureStatus getStatus(float bar);
    String getStatusString(PressureStatus status);
};