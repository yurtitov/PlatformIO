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
    display.begin();

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

    ledSignal.begin();
    ledSignal.showDemo();

    solenoidValve.begin();
    buzzer.begin();

    display.clean();
}

void RefillSystem::update()
{
        // TODO
}
    

void RefillSystem::handleMonitoring()
{
        // TODO
}

void RefillSystem::handleRefilling()
{
        // TODO
}

void RefillSystem::handleAlarm()
{
        // TODO
}

void RefillSystem::handleManual()
{
        // TODO
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
