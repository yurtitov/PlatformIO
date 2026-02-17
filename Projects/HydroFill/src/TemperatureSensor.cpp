#include <TemperatureSensor.h>

TemperatureSensor::TemperatureSensor()
    : _oneWire(TEMPERATURE_SENSOR_DATA_PIN), _sensor(&_oneWire) {}

void TemperatureSensor::begin() {
    _sensor.begin();
}

void TemperatureSensor::update()
{
    _sensor.requestTemperatures();
    _temperature = _sensor.getTempCByIndex(0);
}

float TemperatureSensor::getTemperature()
{
    return _temperature;
}

bool TemperatureSensor::isSensorConnected()
{
    return _temperature != DEVICE_DISCONNECTED_C;
}
