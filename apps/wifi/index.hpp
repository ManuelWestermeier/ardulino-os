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

    void Update()
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
            Text(0, 0, WiFi.SSID(wifiIndex)).Draw();
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

    void ConnectToWifi()
    {
        try
        {
            // Clear the screen and display connecting message
            lcd.clear();
            lcd.home();
            lcd.print("Connecting to WiFi:");
            lcd.setCursor(0, 2);
            lcd.print(utils::setStringSize(WiFi.SSID(wifiIndex), 20)); // Display selected network
            lcd.setCursor(1, 3);
            lcd.print("<<exit | connect>>");

            // Wait for joystick input (guard clause: exit on left movement)
            while (utils::normalizeJoystick(xPin) == 0)
            {
            }

            if (utils::normalizeJoystick(xPin) < 0)
            {
                // Joystick moved left, exit early
                lcd.clear();
                lcd.print("Aborted!");
                delay(1000);
                wifiIndex = -2;
                state = 0;
                return;
            }

            // Wait for joystick release
            while (utils::normalizeJoystick(xPin) != 0)
            {
            }

            CURSOR_OFFSET = 16;

            // Check if the network is open (no password required)
            bool isOpenNetwork = (WiFi.encryptionType(wifiIndex) == WIFI_AUTH_OPEN);

            // Guard clause: skip password input for open networks
            if (isOpenNetwork)
            {
                lcd.clear();
                lcd.print("Connecting to open network...");
                WiFi.begin(WiFi.SSID(wifiIndex)); // Connect without password
            }
            else
            {
                // Prompt for password if needed
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Enter password:");
                delay(1000);

                String defaultPassword = "";                                 // Optional default password
                String *password = input::ReadString({0, &defaultPassword}); // Read user input

                // Guard clause: check if the password is null or empty
                if (password == nullptr || password->length() == 0)
                {
                    lcd.clear();
                    lcd.print("Invalid Password!");
                    delay(2000);
                    wifiIndex = -2;
                    state = 0;
                    return; // Early exit if no password is provided
                }

                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("Connecting...");

                WiFi.begin(WiFi.SSID(wifiIndex), *password); // Connect with password
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

            // Success message
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("Connected!");
            lcd.setCursor(0, 2);
            lcd.print("IP: ");
            lcd.print(WiFi.localIP()); // Show IP address
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

#endif
