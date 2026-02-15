#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <vector>

class I2CScanner
{
public:
    // Сканирует шину и выводит результат в Serial
    static void scanAndPrint();

    // Возвращает список найденных адресов (для программной проверки)
    static std::vector<uint8_t> getDeviceList();

    // Проверяет наличие конкретного устройства по адресу
    static bool isDeviceReady(uint8_t address);
};
