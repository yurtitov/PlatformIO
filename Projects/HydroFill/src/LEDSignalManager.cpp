#include <LEDSignalManager.h>

LED::LED(int pin)
    : _pin(pin) {};

void LED::begin()
{
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
};

void LED::on()
{
    digitalWrite(_pin, HIGH);
};

void LED::off()
{
    digitalWrite(_pin, LOW);
};

void LED::toggle()
{
    digitalWrite(_pin, digitalRead(_pin));
};

LEDSignalManager::LEDSignalManager()
    : _ledGreen(LED_GREEN_PIN), _ledRed(LED_RED_PIN), _ledBlue(LED_BLUE_PIN) {}   

void LEDSignalManager::begin()
{
    _ledGreen.begin();
    _ledRed.begin();
    _ledBlue.begin();
};

void LEDSignalManager::showDemo()
{
    offAll();
    delay(500);
    onAll();
    delay(500);
    offAll();
    delay(500);
    _ledGreen.on();
    delay(500);
    _ledRed.on();
    delay(500);
    _ledBlue.on();
    delay(500);
    _ledGreen.off();
    delay(500);
    _ledRed.off();
    delay(500);
    _ledBlue.off();
    delay(500);
    onAll();
    delay(500);
    offAll();
}

void LEDSignalManager::showMonitoring() 
{
    offAll();
    _ledGreen.on();
}

void LEDSignalManager::showRefilling() 
{
    offAll();
    _ledBlue.on();
}

void LEDSignalManager::showAlarm() 
{
    offAll();
    _ledRed.on();
}

void LEDSignalManager::onAll() 
{
    _ledGreen.on();
    _ledRed.on();
    _ledBlue.on();
}

void LEDSignalManager::offAll() 
{
    _ledGreen.off();
    _ledRed.off();
    _ledBlue.off();
};
