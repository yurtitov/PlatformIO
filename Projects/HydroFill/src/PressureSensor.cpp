#include <PressureSensor.h>

PressureSensor::PressureSensor(uint8_t addr, int sda, int scl) : _addr(addr), _sda(sda), _scl(scl) {}

void PressureSensor::begin() {
    Wire.begin(_sda, _scl);
}

float PressureSensor::readPressure()
{
    long raw_sum = 0;
    int samples = 5;

    for (int i = 0; i < samples; i++)
    {
        Wire.beginTransmission(_addr);
        Wire.write(0xAC);
        Wire.endTransmission();
        delay(50);

        Wire.requestFrom(_addr, (uint8_t)3);
        if (Wire.available() == 3)
        {
            Wire.read(); // Skip status
            uint8_t msb = Wire.read();
            uint8_t lsb = Wire.read();
            raw_sum += (msb << 8) | lsb;
        }
    }

    float raw_avg = (float)raw_sum / samples;
    float pressure_bar = ((raw_avg - RAW_ZERO) / RAW_RANGE) * MAX_BAR;

    return (pressure_bar < 0) ? 0 : pressure_bar;
}

PressureStatus PressureSensor::getStatus(float bar)
{
    if (bar < 0.6)
        return EMPTY_SYSTEM;
    if (bar < 1.2)
        return LOW_PRESSURE;
    if (bar <= 2.2)
        return NORMAL_PRESSURE;
    return HIGH_PRESSURE;
}

String PressureSensor::getStatusString(PressureStatus status)
{
    switch (status)
    {
    case EMPTY_SYSTEM:
        return "АВАРИЯ: ПУСТАЯ СИСТЕМА";
    case LOW_PRESSURE:
        return "ПРЕДУПРЕЖДЕНИЕ: НИЗКОЕ ДАВЛЕНИЕ";
    case NORMAL_PRESSURE:
        return "НОРМА";
    case HIGH_PRESSURE:
        return "ВНИМАНИЕ: ВЫСОКОЕ ДАВЛЕНИЕ";
    default:
        return "ОШИБКА";
    }
}
