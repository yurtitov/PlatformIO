#pragma once

#include <PressureSensor.h>
#include <TemperatureSensor.h>
#include <Display_1_77_TFT_Manager.h>
#include <LEDSignalManager.h>
#include <SolenoidValveManager.h>
#include <BuzzerManager.h>
#include <ButtonManager.h>

#define MAX_RESSURE 2.5
#define MIN_PRESSURE 1.5

enum class State
{
    INIT,
    MONITORING,
    REFILLING,
    ALARM,
    MANUAL
};

class RefillSystem
{
public:
    RefillSystem();
    void begin();
    void update(); // use in loop
private:
    void handleInit();
    void handleMonitoring();
    void handleRefilling();
    void handleAlarm();
    void handleManual();

    bool isNormalPressure(float pressure);
    bool isHighPressue(float pressure);
    bool isLowPressure(float pressure);
    
    void transitionTo(State newState);
    
    static void pressureTask(void *pvParameters);
    static void temperatureTask(void *pvParameters);

    State _currentState = State::INIT;

    PressureSensor pressureSensor;
    LEDSignalManager ledSignal;
    Display_1_77_TFT_Manager display;
    TemperatureSensor temperatureSensor;
    SolenoidValveManager solenoidValve;
    BuzzerManager buzzer;
    ButtonManager button;
};