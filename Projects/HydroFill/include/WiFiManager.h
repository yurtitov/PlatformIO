#pragma once
#include <WiFi.h>

class WiFi_Manager {
public:
    WiFi_Manager(const char* ssid, const char* password);
    void connect();
    bool isConnected();
    int8_t getRSSI();
    void printSignalQuality();

private:
    const char* _ssid;
    const char* _password;
    // Event handler must be static
    static void WiFiEvent(WiFiEvent_t event);
};