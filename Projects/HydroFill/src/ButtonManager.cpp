#include <ButtonManager.h>

ButtonManager::ButtonManager(uint32_t debounce_ms = 50)
    : _pin(BUTTON_PIN), _debounce_ms(debounce_ms) {}

void ButtonManager::begin() { pinMode(_pin, INPUT_PULLUP); }

bool ButtonManager::isPressed() {
    bool currentState = (digitalRead(_pin) == LOW);

    if (currentState != _lastState) {
        _lastDebounceTime = millis();
    }

    if ((millis() - _lastDebounceTime) > _debounce_ms) {
        _stableState = currentState;
    }

    _lastState = currentState;
    return _stableState;
}

bool ButtonManager::wasClicked() {
    bool pressed = isPressed();
    if (pressed && !_wasPressedFlag) {
        _wasPressedFlag = true;
        return true;
    }

    if (!pressed) {
        _wasPressedFlag = false;
    }

    return false;
}
