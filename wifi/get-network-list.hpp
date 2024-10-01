#ifndef WIFI_GET_NETWORK_LIST_HPP
#define WIFI_GET_NETWORK_LIST_HPP

#include "../utils/structs/select.hpp"
#include "../globals.hpp"
#include <WiFi.h> // Ensure WiFi library is included

int WifiScanStart(
    bool showHidden = false,
    bool passive = false,
    uint32_t max_ms_per_chan = 300,
    uint8_t channel = 0,
    const char *ssid = nullptr,
    const uint8_t *bssid = nullptr)
{
    // Set WiFi to station mode and disconnect from an AP if it was previously connected.
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    WiFi.scanDelete();
    return WiFi.scanNetworks(false, showHidden, passive, max_ms_per_chan, channel, ssid, bssid);
}

Select *GetWifiNetworkSelect(int networkCount)
{
    Select *wifiSelect = new Select();
    wifiSelect->optionsLength = networkCount;

    // Allocate new memory for the SSID list
    wifiSelect->options = new String[wifiSelect->optionsLength]; // Allocate new memory
    if (wifiSelect->options == nullptr)
    {
        ClearAppScreen();
        // Handle allocation failure
        Text(1, 1, "Allocation Failed").Draw();
        AppRender::UpdateView();
        delay(1000);
        delete wifiSelect; // Clean up wifiSelect
        wifiSelect = nullptr; // Set pointer to nullptr after deletion
        return nullptr;    // Return null pointer if allocation failed
    }

    // Fill the SSID list
    for (byte i = 0; i < wifiSelect->optionsLength; i++)
    {
        wifiSelect->options[i] = WiFi.SSID(i);
    }

    // Set position if there are more than 2 networks
    if (wifiSelect->optionsLength > 2)
    {
        wifiSelect->pos = 1;
    }

    return wifiSelect; // Return pointer to the allocated list
}

#endif
