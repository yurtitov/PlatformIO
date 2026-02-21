#include "RefillSystem.h"

RefillSystem::RefillSystem()
    : pressureSensor(),
      ledSignal(),
      display(),
      temperatureSensor(),
      solenoidValve(),
      buzzer(),
      button(50) {}

void RefillSystem::begin() {
    pressureSensor.begin();
    xTaskCreate(pressureTask,    // Функция задачи
                "PressureTask",  // Имя задачи
                4096,            // Размер стека
                this,            // Параметры
                1,               // Приоритет
                NULL             // Хендл задачи
    );

    temperatureSensor.begin();
    xTaskCreate(temperatureTask, "TemperatureTask", 4096, this, 1, NULL);

    display.begin();
    ledSignal.begin();
    solenoidValve.begin();
    buzzer.begin();
    button.begin();
}

void RefillSystem::update() {
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

void RefillSystem::handleInit() {
    // get data
    auto [pressure, temperature] = getSensorsData();

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
    if (!isAlarm(pressure, temperature)) {
        transitionTo(State::MONITORING);
        Serial.println(1);
    } else {
        transitionTo(State::ALARM);
        Serial.println(2);
    }
}

void RefillSystem::handleMonitoring() {
    // get data
    auto [pressure, temperature] = getSensorsData();

    // Solenoid valve
    solenoidValve.off();

    // Buzzer
    buzzer.off();

    // LedSignal
    ledSignal.showMonitoring();

    // Display
    display.printInfo(temperature, pressure);

    // action
    if (isAlarm(pressure, temperature)) {
        transitionTo(State::ALARM);
    }
}

void RefillSystem::handleRefilling() {
    // get data
    auto [pressure, temperature] = getSensorsData();

    // Solenoid valve
    solenoidValve.off(); // TODO Add time range

    // Buzzer
    // buzzer.on();

    // LedSignal
    ledSignal.showRefilling();

    // Display
    display.printPumpingWater(pressure, !isNormalPressure(pressure));

    // action
    if (isNormalPressure(pressure)) {
        transitionTo(State::MONITORING);
    }
}

void RefillSystem::handleAlarm() {
    // get data
    auto [pressure, temperature] = getSensorsData();

    // Solenoid valve
    solenoidValve.off();

    // Buzzer
    buzzer.off();

    // LedSignal
    ledSignal.showAlarm();

    // Display
    display.printAlarm(temperature, pressure, !isNormalTemperature(temperature),
                       !isNormalPressure(pressure));

    // action
    if (isPressureCriticallyLow(pressure)) {
        transitionTo(State::REFILLING);
    }

    if (button.wasClicked()) {
        transitionTo(State::MANUAL);
    }

    if (!isAlarm(pressure, temperature)) {
        transitionTo(State::MONITORING);
    }
}

void RefillSystem::handleManual() {
    // get data
    auto [pressure, temperature] = getSensorsData();

    // Solenoid valve
    // Buzzer
    // LedSignal
    // Display
    display.printDebug("Manual");
    
    // action
    if (isPressureCriticallyLow(pressure)) {
        transitionTo(State::REFILLING);
    }
}

bool RefillSystem::isNormalPressure(float pressure) {
    return pressure > ALARM_LOW_PRESSURE && pressure < ALARM_HIGH_PRESSURE;
}

bool RefillSystem::isPressureCriticallyHigh(float pressure) { return pressure >= MAX_RESSURE; }

bool RefillSystem::isPressureCriticallyLow(float pressure) { return pressure <= MIN_PRESSURE; }

bool RefillSystem::isNormalTemperature(float temperature) {
    return temperature > ALARM_LOW_TEMPERATURE && temperature < ALARM_HIGH_TEMPERATURE;
}

bool RefillSystem::isAlarm(float pressure, float temperature) {
    return !isNormalPressure(pressure) || !isNormalTemperature(temperature);
}

void RefillSystem::transitionTo(State newState) {
    _currentState = newState;
    display.clean();
}

void RefillSystem::pressureTask(void* pvParameters) {
    RefillSystem* system = static_cast<RefillSystem*>(pvParameters);

    while (true) {
        system->pressureSensor.update();  // Опрашиваем датчик (это занимает ~750мс из-за delay)
        vTaskDelay(pdMS_TO_TICKS(100));   // Небольшая пауза между циклами опроса
    }
}

void RefillSystem::temperatureTask(void* pvParameters) {
    RefillSystem* system = static_cast<RefillSystem*>(pvParameters);
    while (true) {
        system->temperatureSensor.update();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Return pressure, temperature tuple
std::tuple<float, float> RefillSystem::getSensorsData() {
    float pressure = pressureSensor.getLatestPressure();
    float temperature = temperatureSensor.getTemperature();
    return {1.19, 50};
}
