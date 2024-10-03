#ifndef APPS_WIFI_FAST_CONNECT_HPP
#define APPS_WIFI_FAST_CONNECT_HPP

#include "./connect-to-wifi.hpp"
#include "./index.hpp"

void WifiApp::FastConnect()
{
    try
    {
        ClearAppScreen();                 // Clear the display before scanning
        Text(1, 1, "Scanning...").Draw(); // Display scanning message
        AppRender::UpdateView();          // Update the screen

        // Scan for available WiFi networks
        int wifiCount = WifiScanStart(true, true);
        if (wifiCount < 1)
        {
            ClearAppScreen();
            Text(1, 1, "No WiFi").Draw();
            Text(2, 1, "networks found").Draw();
            AppRender::UpdateView();
            delay(1000);
            return;
        }

        int wifiIndex = 0;
        bool connectionAttempted = false;
        bool isOpenNetwork = false; // Declare isOpenNetwork here so it can be used later

        // Loop through WiFi networks for selection with the joystick
        while (wifiIndex < wifiCount && wifiIndex > -1)
        {
            // Get current WiFi network's SSID and encryption type
            String ssid = WiFi.SSID(wifiIndex);
            isOpenNetwork = (WiFi.encryptionType(wifiIndex) == WIFI_AUTH_OPEN); // Assign the value here

            // Check if the network is either open or its SSID is in wifisConnected
            if (isOpenNetwork || wifisConnected.has(ssid))
            {
                // Display the current WiFi network name
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print(utils::setStringSize(ssid, 20));
                lcd.setCursor(0, 2);
                lcd.print("<<next  |  connect>>");

                // Wait for joystick input (left to skip, right to select, or stay idle)
                int swipeDirection = 0;
                // wait for joystick input (left to skip, right to select, or stay idle)
                while ((swipeDirection = utils::normalizeJoystick(xPin)) == 0)
                {
                }
                lcd.clear();
                lcd.setCursor(5, 1);
                lcd.print(swipeDirection < 0 ? "next" : "selected");
                lcd.clear();
                // wait for no movement
                while (utils::normalizeJoystick(xPin) != 0)
                {
                }

                if (swipeDirection < 0)
                {
                    // Move to the next network
                    wifiIndex++;
                    // all networks shown
                    if (wifiIndex == wifiCount)
                    {
                        lcd.clear();
                        lcd.setCursor(3, 1);
                        lcd.print("not connected");
                        delay(1000);
                        lcd.clear();
                        return;
                    }
                }
                else
                {
                    // User selected this network
                    connectionAttempted = true;
                    break;
                }
            }
            else
            {
                // If the network is not open and not in wifisConnected, skip to the next
                wifiIndex++;
                if (wifiIndex >= wifiCount)
                    wifiIndex = 0; // Loop back to first network
            }
        }

        if (!connectionAttempted)
            return; // Exit if no network was selected

        // Now, attempt to connect to the selected network
        String password = wifisConnected.get(WiFi.SSID(wifiIndex)); // Get password (if any)

        // Attempt to connect: open network (no password) or known network with stored password
        if (isOpenNetwork)
        {
            WiFi.begin(WiFi.SSID(wifiIndex)); // Open network, no password
        }
        else
        {
            WiFi.begin(WiFi.SSID(wifiIndex), password); // Secured network with password
        }

        // Guard clause: handle timeout or failed connection
        unsigned long startTime = millis();
        const unsigned long timeout = 10000; // 10-second timeout

        while (WiFi.status() != WL_CONNECTED)
        {
            if (millis() - startTime > timeout)
            {
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("Connection Failed!");
                delay(2000);    // Display failure message
                wifiIndex = -2; // Reset selection
                state = 0;
                return; // Early exit on connection failure
            }
        }

        // Connection success message
        lcd.clear();
        lcd.setCursor(2, 1);
        lcd.print("Connected!");
        lcd.setCursor(0, 2);
        lcd.print(utils::setStringSize(WiFi.SSID(wifiIndex), 20));
        lcd.setCursor(0, 3);
        lcd.print("IP: ");
        lcd.print(utils::setStringSize(WiFi.localIP().toString(), 16)); // Show IP address
        delay(2000);

        // Reset state for further actions
        wifiIndex = -2;
        state = 0;
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
    catch (...)
    {
        // Catch any other unhandled errors
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Unknown error!");
        delay(3000); // Display generic error
        wifiIndex = -2;
        state = 0;
    }
}

#endif // APPS_WIFI_FAST_CONNECT_HPP