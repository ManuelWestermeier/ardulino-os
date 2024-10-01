#ifndef UTILS_STRUCTS_WIFI_DATA_HPP
#define UTILS_STRUCTS_WIFI_DATA_HPP

#include <WiFi.h>

struct WifiData
{
    String ssid;
    int32_t rssi;
    int32_t channel;
    uint8_t authMode; // Changed to uint8_t for clarity

    WifiData(int i)
    {
        // Check if index is within valid range
        if (i >= 0 && i < WiFi.scanComplete())
        {
            ssid = WiFi.SSID(i);
            rssi = WiFi.RSSI(i);
            channel = WiFi.channel(i);
            authMode = WiFi.encryptionType(i);
        }
        else
        {
            Serial.println("ERROR: Index out of range: ");
            Serial.print(i);
            ssid = "Unknown"; // Assign a default value
            rssi = 0;
            channel = 0;
            authMode = 0; // Default value for auth mode
        }
    }
};

#endif