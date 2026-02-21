#include <PressureSensor.h>

PressureSensor::PressureSensor(float alpha)
    : _addr(PRESSURE_SENSOR_ADDR), _sda(I2C_SDA), _scl(I2C_SCL), _alpha(alpha) {}

void PressureSensor::begin() { Wire.begin(_sda, _scl); }

void PressureSensor::update() {
    // 1. Получаем "сырое" значение (можно без усреднения samples, фильтр сделает это лучше)
    Wire.beginTransmission(_addr);
    Wire.write(0xAC);
    Wire.endTransmission();
    vTaskDelay(pdMS_TO_TICKS(75));

    Wire.requestFrom(_addr, (uint8_t)3);
    if (Wire.available() == 3) {
        Wire.read();
        uint16_t raw = (Wire.read() << 8) | Wire.read();

        // 2. Пересчет в бары
        float current_bar = ((float)(raw - RAW_ZERO) / RAW_RANGE) * MAX_BAR;
        if (current_bar < 0) current_bar = 0;

        // 3. Экспоненциальный фильтр
        if (_filteredPressure < 0) {
            // Первый замер после включения — просто сохраняем как есть
            _filteredPressure = current_bar;
        } else {
            // Математика фильтра
            // При (alpha = 0.2)(рекомендуется) : Если давление резко прыгнет с 1.0 до 2.0 бар,
            // прибор покажет это не мгновенно, а плавно "доплывет" до 2.0 за несколько итераций.
            // Это уберет случайные всплески от работы насоса или гидроударов.
            // При (alpha = 0.8) : Фильтр почти не работает, реакция мгновенная,
            // но значения будут "дрожать" в Serial.
            _filteredPressure = (_alpha * current_bar) + ((1.0f - _alpha) * _filteredPressure);
        }
    }
}

float PressureSensor::getLatestPressure() { return _filteredPressure; }