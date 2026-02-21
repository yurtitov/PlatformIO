#include "I2CScanner.h"

void I2CScanner::scanAndPrint() {
    Serial.println("[I2C] Starting scan...");
    std::vector<uint8_t> devices = getDeviceList();

    if (devices.empty()) {
        Serial.println("[I2C] No devices found. Check wiring and Pull-ups!");
    } else {
        Serial.printf("[I2C] Found %d device(s):\n", devices.size());
        for (uint8_t addr : devices) {
            Serial.printf(" - 0x%02X\n", addr);
        }
    }
}

std::vector<uint8_t> I2CScanner::getDeviceList() {
    std::vector<uint8_t> foundDevices;
    for (uint8_t address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        if (Wire.endTransmission() == 0) {
            foundDevices.push_back(address);
        }
    }
    return foundDevices;
}

bool I2CScanner::isDeviceReady(uint8_t address) {
    Wire.beginTransmission(address);
    return (Wire.endTransmission() == 0);
}
