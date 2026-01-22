#pragma once

class Led
{
private:
    int pin_;
public:
    Led(int pin);

    void init();
    
    void on();
    void off();

    bool isOn();
};