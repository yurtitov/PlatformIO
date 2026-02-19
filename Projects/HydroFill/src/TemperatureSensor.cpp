#include <TemperatureSensor.h>

TemperatureSensor::TemperatureSensor()
    : _oneWire(TEMPERATURE_SENSOR_DATA_PIN), _sensor(&_oneWire) {}

void TemperatureSensor::begin() {
    _sensor.begin();
    _sensor.setWaitForConversion(false); // Отключаем блокирующее ожидание
}

void TemperatureSensor::update()
{
    _sensor.requestTemperatures();
    // Вместо того чтобы ждать внутри библиотеки, 
    // FreeRTOS переключит контекст на другие задачи на эти 750мс
    vTaskDelay(pdMS_TO_TICKS(750)); 
    
    float temp = _sensor.getTempCByIndex(0);
    if (temp != DEVICE_DISCONNECTED_C) {
        _temperature = temp;
    }
}

float TemperatureSensor::getTemperature()
{
    return _temperature;
}

bool TemperatureSensor::isSensorConnected()
{
    return _temperature != DEVICE_DISCONNECTED_C;
}
