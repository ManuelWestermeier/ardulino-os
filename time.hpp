#ifndef TIME_HPP
#define TIME_HPP

#include "./globals.hpp"
#include "./wifi/on-wifi-change.hpp"

// Update interval for NTP time (in milliseconds)
const long utcOffsetInSeconds = 0; // Set your UTC offset here

namespace Time
{
    WiFiUDP ntpUDP;
    NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

    unsigned long startTimeOffset = 0;

    void UpdateData(bool isConnected)
    {
        if (!isConnected)
            return;
        timeClient.begin();
        while (!timeClient.update())
        {
            timeClient.forceUpdate(); // Fetch time from NTP server
        }
        startTimeOffset = timeClient.getEpochTime() - millis();
    }

    unsigned long GetTime()
    {
        return startTimeOffset + millis();
    }

    void Init()
    {
        WifiMenager::onWifiChangeCallback.Add(UpdateData);
    }
};

using Time::GetTime;

#endif
