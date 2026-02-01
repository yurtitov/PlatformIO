#include <Arduino.h>
#include <WiFiManager.h>
#include <TimeManager.h>

const char *WIFI_SSID = "some_ssid";
const char *WIFI_PASS = "some_pass";
const char *NTP_SERVER = "pool.ntp.org";
const long GMT_OFFSET_SEC = 7200; // KLD (GMT+2)

WiFi_Manager wifi(WIFI_SSID, WIFI_PASS);
TimeManager timeService(NTP_SERVER, GMT_OFFSET_SEC, 0);

void setup()
{
  Serial.begin(115200);
  delay(2000);
  wifi.connect();
  timeService.begin();
}

void loop()
{
  if (wifi.isConnected())
  {
    struct tm timeinfo;
    if (getLocalTime(&timeinfo))
    {
      Serial.print("[DATA] " + timeService.getFormattedTime());
      Serial.print(" | ");
      wifi.printSignalQuality();
    }
  }
  else
  {
    Serial.println("[System] Waiting for WiFi...");
  }
  delay(5000);
}
