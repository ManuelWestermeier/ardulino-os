#ifndef APPS_WIFI_UPDATE_HPP
#define APPS_WIFI_UPDATE_HPP

#include "./index.hpp"

void WifiApp::Update()
{
    try
    {
        // set title to "Wifi   (x if offline or y if online)"
        char title[11]; // 10 characters + null terminator
        strcpy(title, WiFi.status() == WL_CONNECTED ? "WiFi   (y)" : "WiFi   (x)");
        SetAppTitle(title, 10);

        if (wifiIndex == -1)
        {
            ClearAppScreen();
            Text(1, 1, "No Network Selected").Draw();
            AppRender::UpdateView();
            delay(1000);
            wifiIndex = -2;
            state = 0;
        }
        else if (wifiIndex > -1)
        {
            ClearAppScreen();
            Text(0, 0, utils::setStringSize(WiFi.SSID(wifiIndex), 19)).Draw();
            connectToWifiButton.Draw();
            abortWifiButton.Draw();
        }
        else if (state == 0)
        {
            ClearAppScreen();
            // Render SSID or "No Wifi"
            Text(0, 1, WiFi.status() == WL_CONNECTED ? utils::setStringSize(WiFi.SSID(), 17).c_str() : "No Wifi").Draw();
            // Display the button for initiating WiFi scanning
            startScanButton.Draw();
            // Display the button for initiating WiFi scanning
            fastConnectButton.Draw();
        }
        else if (state == 1)
        {
            if (count == 50)
            {
                ClearAppScreen();                 // Clear the display before scanning
                Text(1, 1, "Scanning...").Draw(); // Display searching message
                AppRender::UpdateView();          // Update the screen

                // Scan for available WiFi networks
                int wifiCount = WifiScanStart(true, true);

                if (wifiCount > 0) // If networks are found
                {
                    // Display processing message
                    Text(1, 1, "Processing...").Draw();
                    AppRender::UpdateView();

                    ClearWifiSelect(); // Free any previously allocated wifiSelect

                    wifiSelect = GetWifiNetworkSelect(wifiCount); // Get the new list of WiFi networks
                    if (wifiSelect != nullptr)
                    {
                        wifiSelect->Update(); // Update the selection widget
                    }
                    else
                    {
                        // Handle allocation failure
                        Text(1, 1, "Failed to allocate memory").Draw();
                        AppRender::UpdateView();
                        delay(1000);
                        state = 0; // Reset state on failure
                    }
                }
                else // If no networks were found
                {
                    ClearAppScreen();
                    Text(1, 1, "0 Networks Found").Draw();
                    AppRender::UpdateView();
                    delay(1000);
                    ClearAppScreen();
                    state = 0; // Reset to initial state
                }

                count = 0; // Reset the count after scanning
            }
            else
            {
                if (wifiSelect != nullptr)
                {
                    wifiSelect->Update(); // Continuously update the select list if it exists
                }
                count++; // Increment the count until the next scan
            }
        }
    }
    catch (const std::exception &e)
    {
        // Handle any unexpected errors
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Error occurred:");
        lcd.setCursor(0, 2);
        lcd.print(e.what()); // Display error message
        delay(3000);         // Display error for 3 seconds
        wifiIndex = -2;
        state = 0;
    }
}

#endif //