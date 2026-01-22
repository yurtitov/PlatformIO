#include <led.h>
#include <Arduino.h>

Led::Led(int pin) : pin_(pin) {}

void Led::init() {
    pinMode(pin_, OUTPUT);
    off();
}

void Led::on() {
    digitalWrite(pin_, HIGH);
}

void Led::off() {
    digitalWrite(pin_, LOW);
}

bool Led::isOn() {
    return digitalRead(pin_) == HIGH;
}