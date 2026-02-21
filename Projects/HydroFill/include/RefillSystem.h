#pragma once

#include <ButtonManager.h>
#include <BuzzerManager.h>
#include <Display_1_77_TFT_Manager.h>
#include <LEDSignalManager.h>
#include <PressureSensor.h>
#include <SolenoidValveManager.h>
#include <TemperatureSensor.h>

#define MAX_RESSURE 2.7
#define ALARM_HIGH_PRESSURE 2.4
#define ALARM_LOW_PRESSURE 1.5
#define MIN_PRESSURE 1.2

#define ALARM_HIGH_TEMPERATURE 75.00
#define ALARM_LOW_TEMPERATURE 35.00

enum class State { INIT, MONITORING, REFILLING, ALARM, MANUAL };

class RefillSystem {
public:
    RefillSystem();
    void begin();
    void update();  // use in loop
private:
    void handleInit();
    void handleMonitoring();
    void handleRefilling();
    void handleAlarm();
    void handleManual();

    bool isNormalPressure(float pressure);
    bool isPressureCriticallyHigh(float pressure);
    bool isPressureCriticallyLow(float pressure);
    bool isNormalTemperature(float temperature);
    bool isAlarm(float pressure, float temperature);

    void transitionTo(State newState);

    std::tuple<float, float> getSensorsData();

    static void pressureTask(void* pvParameters);
    static void temperatureTask(void* pvParameters);

    State _currentState = State::INIT;

    PressureSensor pressureSensor;
    LEDSignalManager ledSignal;
    Display_1_77_TFT_Manager display;
    TemperatureSensor temperatureSensor;
    SolenoidValveManager solenoidValve;
    BuzzerManager buzzer;
    ButtonManager button;
};