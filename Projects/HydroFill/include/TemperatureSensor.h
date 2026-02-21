#pragma once

#include <DallasTemperature.h>
#include <OneWire.h>

#define TEMPERATURE_SENSOR_DATA_PIN 4

class TemperatureSensor {
public:
    TemperatureSensor();
    void begin();
    void update();
    float getTemperature();
    bool isSensorConnected();

private:
    DallasTemperature _sensor;
    OneWire _oneWire;
    volatile float _temperature = -127.0f;
};