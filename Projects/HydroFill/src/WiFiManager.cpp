#include <WiFiManager.h>

WiFi_Manager::WiFi_Manager(const char *ssid, const char *password)
    : _ssid(ssid), _password(password) {}

void WiFi_Manager::WiFiEvent(WiFiEvent_t event)
{
    switch (event)
    {
    case ARDUINO_EVENT_WIFI_STA_CONNECTED:
        Serial.println("[WiFi] Connected to AP");
        break;
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
        Serial.print("[WiFi] IP: ");
        Serial.println(WiFi.localIP());
        break;
    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
        Serial.println("[WiFi] Lost connection. Reconnecting...");
        // Automatic reconnect
        WiFi.begin();
        break;
    default:
        break;
    }
}

void WiFi_Manager::connect()
{
    if (WiFi.status() == WL_CONNECTED)
        return;

    WiFi.disconnect(true); // Сброс старых настроек

    // Регистрируем обработчик событий
    WiFi.onEvent(WiFiEvent);

    WiFi.mode(WIFI_STA);
    WiFi.begin(_ssid, _password);

    Serial.printf("[WiFi] Connecting to %s...", _ssid);

    // Блокируем только при ПЕРВОМ запуске, если нужно дождаться сети
    unsigned long startAttempt = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startAttempt < 10000)
    {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("\n[WiFi] Initial connection failed. Will keep trying in background.");
    }
}

bool WiFi_Manager::isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

int8_t WiFi_Manager::getRSSI()
{
    return WiFi.RSSI();
}

void WiFi_Manager::printSignalQuality()
{
    int8_t rssi = getRSSI();
    Serial.printf("[WiFi] Signal strength: % d dBm (", rssi);

    if (rssi >= -50)
        Serial.print("Excellent");
    else if (rssi >= -60)
        Serial.print("Good");
    else if (rssi >= -70)
        Serial.print("Fair");
    else if (rssi >= -80)
        Serial.print("Weak");
    else
        Serial.print("Very Poor");

    Serial.println(")");
}