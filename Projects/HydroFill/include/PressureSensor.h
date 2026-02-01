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
public:
    PressureSensor(uint8_t addr, int sda, int scl, float alpha = 0.2f); // alpha - коэффициент сглаживания
    void begin();

    // Этот метод будет вызываться внутри потока
    void update();

    // Эти методы для чтения из loop()
    float getLatestPressure();
    PressureStatus getStatus();
    String getStatusString(PressureStatus status);

private:
    uint8_t _addr;
    int _sda, _scl;
    float _alpha; // Коэффициент фильтрации (0.1 - сильно сглажено, 0.9 - почти без фильтра)

    volatile float _filteredPressure = -1.0f; // -1 для инициализации первым замером

    const float MAX_BAR = 10.0;
    const int RAW_ZERO = 6595;
    const int RAW_RANGE = 13107;
};