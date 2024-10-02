#include "../../globals.hpp"

void WifiApp::Update()
{
    SetAppTitle("Wifi", 4); // Set the title of the app to "WiFi"
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
        // Display the button for initiating WiFi scanning
        startScanButton.Draw();
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
