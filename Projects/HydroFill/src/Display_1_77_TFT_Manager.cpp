#include <Display_1_77_TFT_Manager.h>

Display_1_77_TFT_Manager::Display_1_77_TFT_Manager()
    : _display(DISPLAY_PIN_7_CS, DISPLAY_PIN_6_RS, DISPLAY_PIN_4_SDA, DISPLAY_PIN_3_SCK, DISPLAY_PIN_5_RES) {}

void Display_1_77_TFT_Manager::begin()
{
    _display.initR(INITR_BLACKTAB);
    _display.setRotation(1);
    _display.fillScreen(ST77XX_BLACK);

    _display.setCursor(10, 30);
    _display.setTextColor(ST77XX_GREEN, ST77XX_BLACK);
    _display.setTextSize(6);
    _display.println("YTTY");
}

void Display_1_77_TFT_Manager::clean()
{
    _display.fillScreen(ST77XX_BLACK);
}

void Display_1_77_TFT_Manager::printInfo(float temperature, float pressure)
{
    _display.setCursor(10, 15);
    _display.setTextColor(ST77XX_GREEN, ST77XX_BLACK);
    _display.setTextSize(3);
    _display.println("OK");

    _display.setCursor(10, 60);
    _display.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    _display.setTextSize(1.5);
    _display.print("p = ");
    _display.setTextSize(2);
    _display.print(pressure);
    _display.println(" bar");

    _display.setCursor(10, 90);
    _display.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    _display.setTextSize(1);
    _display.print("t = ");
    _display.setTextSize(2);
    _display.print(temperature);
    _display.println(" \367C");
}

void Display_1_77_TFT_Manager::printPumpingWater(int duration_millis, float pressure)
{
    // TODO
}

void Display_1_77_TFT_Manager::printAlarm(String cause)
{
    _display.fillScreen(ST7735_BLACK);

    // Рисуем треугольник в центре верхней части (x=80 для экрана 160px)
    drawWarning(80, 10, 20);

    _display.setCursor(10, 50);
    _display.setTextColor(ST77XX_RED);
    _display.setTextSize(2);
    _display.println("ALARM!");

    _display.setCursor(10, 80);
    _display.setTextSize(1);
    _display.setTextColor(ST77XX_WHITE);
    _display.println(cause);
}

void Display_1_77_TFT_Manager::drawWarning(int16_t x, int16_t y, int16_t size)
{
    // 1. Рисуем красный треугольник
    // x, y — координаты верхней вершины
    _display.fillTriangle(
        x, y,               // Верх
        x - size, y + size, // Лево-низ
        x + size, y + size, // Право-низ
        ST77XX_RED);

    // 2. Рисуем восклицательный знак (белым цветом)
    // Линия (верхняя часть знака)
    int16_t line_height = size / 2;
    _display.fillRect(x - 1, y + (size / 4), 2, line_height, ST77XX_WHITE);

    // Точка (нижняя часть знака)
    _display.fillRect(x - 1, y + size - (size / 6), 2, 2, ST77XX_WHITE);
}
