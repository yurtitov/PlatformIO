#pragma once

#include <Arduino.h>

#define BUTTON_PIN 21

class ButtonManager {
public:
    ButtonManager(uint32_t debounce_ms);
    void begin();
    // Возвращает текущее состояние (true - нажата)
    bool isPressed();
    // Возвращает true только в момент нажатия (одиночный клик)
    bool wasClicked();

private:
    uint8_t _pin;
    uint32_t _debounce_ms;
    uint32_t _lastDebounceTime = 0;
    bool _lastState = false;
    bool _stableState = false;
    bool _wasPressedFlag = false;
};