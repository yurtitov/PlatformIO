#pragma
#include <Arduino.h>
#include <time.h>

class TimeManager
{
public:
    TimeManager(const char *ntpServer, long gmtOffset_sec, int dayLightOffset_sec);
    void begin();
    String getFormattedTime(const char *format = "%Y-%m-%d %H:%M:%S");
    bool isReady();

private:
    const char *_ntpServer;
    long _gmtOffset_sec;
    int _daylightOffset_sec;
};