#include "TimeManager.h"

TimeManager::TimeManager(const char *ntpServer, long gmtOffset_sec, int daylightOffset_sec)
    : _ntpServer(ntpServer), _gmtOffset_sec(gmtOffset_sec), _daylightOffset_sec(daylightOffset_sec) {}

void TimeManager::begin()
{
    configTime(_gmtOffset_sec, _daylightOffset_sec, _ntpServer);
}

bool TimeManager::isReady()
{
    struct tm timeinfo;
    return getLocalTime(&timeinfo);
}

String TimeManager::getFormattedTime(const char *format)
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        return "Time Sync Error";
    }
    char timeStringBuff[64];
    strftime(timeStringBuff, sizeof(timeStringBuff), format, &timeinfo);
    return String(timeStringBuff);
}
