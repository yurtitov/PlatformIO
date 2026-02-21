#include "BuzzerManager.h"

BuzzerManager::BuzzerManager() : _pin(BUZZER_PIN) {}

void BuzzerManager::begin() { pinMode(_pin, OUTPUT); }

void BuzzerManager::on() { digitalWrite(_pin, HIGH); }

void BuzzerManager::off() { digitalWrite(_pin, LOW); }
