#include <SolenoidValveManager.h>

SolenoidValveManager::SolenoidValveManager() : _pin(SOLENOID_VALVE_PIN) {}

void SolenoidValveManager::begin() {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
}

void SolenoidValveManager::on() { digitalWrite(_pin, HIGH); }

void SolenoidValveManager::off() { digitalWrite(_pin, LOW); }
