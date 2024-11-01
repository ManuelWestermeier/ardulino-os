#ifndef WIFI_ON_WIFI_CHANGE_HPP
#define WIFI_ON_WIFI_CHANGE_HPP

#include "../globals.hpp"
#include "../utils/structs/list.hpp"

namespace WifiMenager
{
    bool isConnectedToWifi = false;

    List<void (*)(bool), int> onWifiChangeCallback(0);

    void Update()
    {
        bool isConnected = WiFi.status() == WL_CONNECTED;

        if (isConnectedToWifi != isConnected)
        {
            for (int i = 0; i < onWifiChangeCallback.size; i++)
                onWifiChangeCallback.data[i](isConnected);
        }

        isConnectedToWifi = isConnected;
    }
}

#endif