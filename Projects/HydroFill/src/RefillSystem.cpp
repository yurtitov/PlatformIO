#include "RefillSystem.h"

RefillSystem::RefillSystem()
    : 
    pressureSensor(),
    ledSignal(),
    display(),
    temperatureSensor(),
    solenoidValve(),
    buzzer()
    {}

void RefillSystem::begin()
{
    pressureSensor.begin();
    xTaskCreate(
        pressureTask,   // Функция задачи
        "PressureTask", // Имя задачи
        4096,           // Размер стека
        this,           // Параметры
        1,              // Приоритет
        NULL            // Хендл задачи
    );

    temperatureSensor.begin();
    xTaskCreate(
        temperatureTask,
        "TemperatureTask",
        4096,
        this,
        1,
        NULL
    );

    display.begin();
    ledSignal.begin();
    solenoidValve.begin();
    buzzer.begin();
}

void RefillSystem::update()
{
    unsigned long now = millis();

    switch (_currentState) {
        case State::INIT:
            handleInit();
            break;
        case State::MONITORING:
            handleMonitoring();
            break;
        case State::REFILLING:
            handleRefilling();
            break;
        case State::ALARM:
            handleAlarm();
            break;
        case State::MANUAL:
            handleManual();
            break;
        default:
            break;
    }
}
    
void RefillSystem::handleInit()
{
    // get data
    float pressure = pressureSensor.getLatestPressure();
    float temperature = temperatureSensor.getTemperature();

    // Solenoid valve
    solenoidValve.off();

    // Buzzer
    buzzer.off();
    
    // LedSignal
    ledSignal.showDemo();

    // Display
    display.printDemo();
    display.clean();

    // action
    if (isNormalPressure(pressure)) {
        transitionTo(State::MONITORING);
    } else {
        transitionTo(State::ALARM);
    }
}

void RefillSystem::handleMonitoring()
{
    // get data
    float pressure = pressureSensor.getLatestPressure();
    float temperature = temperatureSensor.getTemperature();

    // Solenoid valve
    solenoidValve.off();

    // Buzzer
    buzzer.off();
    
    // LedSignal
    ledSignal.showMonitoring();

    // Display
    display.printInfo(temperature, pressure);

    // action
    if (!isNormalPressure(pressure)) {
        transitionTo(State::ALARM);
    }
}

void RefillSystem::handleRefilling()
{
    // get data
    // Solenoid valve
    // Buzzer
    // LedSignal
    // Display
    display.printDebug("Refilling");
    // action
}

void RefillSystem::handleAlarm()
{
    // get data
    // Solenoid valve
    // Buzzer
    // LedSignal
    // Display
    display.printDebug("Alarm");
    // action
}

void RefillSystem::handleManual()
{
    // get data
    // Solenoid valve
    // Buzzer
    // LedSignal
    // Display
    display.printDebug("Manual");
    // action
}

bool RefillSystem::isNormalPressure(float pressure)
{
    return pressure > MIN_PRESSURE && pressure < MAX_RESSURE;
}

bool RefillSystem::isHighPressue(float pressure)
{
    return pressure >= MAX_RESSURE;
}

bool RefillSystem::isLowPressure(float pressure)
{
    return pressure <= MIN_PRESSURE;
}

void RefillSystem::transitionTo(State newState)
{
    _currentState = newState;
}

void RefillSystem::pressureTask(void *pvParameters)
{
    RefillSystem* system = static_cast<RefillSystem*>(pvParameters);

    while (true)
    {
        system->pressureSensor.update();  // Опрашиваем датчик (это занимает ~750мс из-за delay)
        vTaskDelay(pdMS_TO_TICKS(100));   // Небольшая пауза между циклами опроса
    }
}


void RefillSystem::temperatureTask(void *pvParameters)
{
    RefillSystem* system = static_cast<RefillSystem*>(pvParameters);
    while ( true)
    {
        system->temperatureSensor.update();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
