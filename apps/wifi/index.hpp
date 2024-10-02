#ifndef APPS_WIFI_INDEX_HPP
#define APPS_WIFI_INDEX_HPP

#include "../../utils/structs/pos.hpp"
#include "../../utils/structs/clickable.hpp"
#include "../../utils/structs/text.hpp"
#include "../../utils/structs/select.hpp"
#include "../../globals.hpp"
#include "../../utils/index.hpp"
#include "../../read/index.hpp"
#include "../../cursor.hpp"
#include "../../app-renderer.hpp"
#include "../../wifi/get-network-list.hpp"

namespace WifiApp
{
    Select *wifiSelect = nullptr;                          // Dynamically allocated Select object for WiFi networks
    Clickable startScanButton{1, 1, 11, "WifiScan", 8};    // Start WiFi scan button
    Clickable connectToWifiButton{1, 1, 10, "Connect", 7}; // Connect button
    Clickable abortWifiButton{2, 1, 8, "Abort", 5};        // Abort button (Corrected label)

    byte state = 0;
    byte count = 50; // Counter to manage scanning delay and updates
    int wifiIndex = -2;

    void ClearWifiSelect()
    {
        if (wifiSelect != nullptr)
        {
            delete[] wifiSelect->options; // Free memory allocated for options
            delete wifiSelect;            // Free the wifiSelect itself
            wifiSelect = nullptr;         // Avoid dangling pointer
        }
    }

    void Update();

    void Submit()
    {
        if (state == 1 && wifiSelect != nullptr)
        {
            wifiSelect->OnClick(); // Handle the submit event for the selected network
        }
    }

    void Scroll(signed char direction)
    {
        if (state == 1 && wifiSelect != nullptr)
        {
            wifiSelect->Scroll(direction); // Allow scrolling through the network list
        }
    }

    void ConnectToWifi();

    void OnClick(Pos pos)
    {
        if (wifiIndex > -1)
        {
            if (connectToWifiButton.collidesWith(pos))
            {
                ConnectToWifi();
            }
            else if (abortWifiButton.collidesWith(pos))
            {
                wifiIndex = -2;
                state = 0;
            }
        }
        else if (state == 0 && startScanButton.collidesWith(pos))
        {
            state = 1;        // Change state to scanning
            ClearAppScreen(); // Clear the screen before scanning
        }
        else if (state == 1 && wifiSelect != nullptr)
        {
            wifiIndex = wifiSelect->OnClick(); // Handle click events for network selection
        }
    }
}

#include "./connect-to-wifi.hpp"
#include "./update.hpp"

#endif
