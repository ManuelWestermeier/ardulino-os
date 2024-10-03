#ifndef WIFI_ASYNC_CONNECT_HPP
#define WIFI_ASYNC_CONNECT_HPP

#include "../utils/structs/stored-map.hpp"
#include "../globals.hpp"

FlashHashMap wifisConnectedAsync("wifis");

void AsyncWifiTask(void *parameter)
{
    Serial.println("Starting WiFi scan...");

    try
    {
        // Set WiFi to station mode and disconnect from an AP if it was previously connected.
        WiFi.mode(WIFI_STA);
        WiFi.disconnect();
        WiFi.scanDelete();
        int wifiCount = WiFi.scanNetworks(false, true, true);

        Serial.print("Networks found: ");
        Serial.println(wifiCount);

        if (wifiCount < 1)
        {
            Serial.println("No networks found. Terminating task.");
            vTaskDelete(NULL); // No networks found, terminate the task
            return;
        }

        int wifiIndex = 0;

        // Loop through WiFi networks until a connection is made
        while (wifiIndex < wifiCount)
        {
            String ssid = WiFi.SSID(wifiIndex);
            bool isOpenNetwork = (WiFi.encryptionType(wifiIndex) == WIFI_AUTH_OPEN);

            Serial.print("Trying to connect to SSID: ");
            Serial.println(ssid);

            if (isOpenNetwork || wifisConnectedAsync.has(ssid))
            {
                String password = wifisConnectedAsync.get(ssid); // Get password if available

                // Try connecting to the network
                if (isOpenNetwork)
                {
                    Serial.print("Connecting to open network: ");
                    Serial.println(ssid);
                    WiFi.begin(ssid.c_str()); // Open network, no password
                }
                else
                {
                    Serial.print("Connecting to secured network: ");
                    Serial.println(ssid);
                    WiFi.begin(ssid.c_str(), password.c_str()); // Secured network with password
                }

                unsigned long startTime = millis();
                const unsigned long timeout = 10000; // 10-second timeout

                // Wait for connection or timeout
                while (WiFi.status() != WL_CONNECTED)
                {
                    if (millis() - startTime > timeout)
                    {
                        Serial.print("Connection to ");
                        Serial.print(ssid);
                        Serial.println(" failed. Trying next network.");
                        break; // Connection failed, move to the next network
                    }
                }

                // If connected, log the success and stop searching
                if (WiFi.status() == WL_CONNECTED)
                {
                    Serial.print("Successfully connected to ");
                    Serial.println(ssid);
                    Serial.print("IP address: ");
                    Serial.println(WiFi.localIP());
                    vTaskDelete(NULL); // Successfully connected, terminate the task
                    return;
                }
            }

            // Move to the next network if connection failed
            wifiIndex++;
        }

        // No successful connection, terminate the task
        Serial.println("No successful connection made. Terminating task.");
        vTaskDelete(NULL);
    }
    catch (...)
    {
        // Handle any errors and terminate the task
        Serial.println("An error occurred during WiFi connection attempt.");
        vTaskDelete(NULL);
    }
}

void AsyncWifiConnect()
{
    // Create a background task for asynchronous WiFi connection
    xTaskCreate(
        AsyncWifiTask,   // Task function
        "AsyncWifiTask", // Name of the task
        10000,           // Stack size (in words)
        NULL,            // Task input parameter
        1,               // Priority of the task
        NULL             // Task handle
    );
}

#endif // WIFI_ASYNC_CONNECT_HPP
