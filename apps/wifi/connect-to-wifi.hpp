#include "../../globals.hpp"

#include "../../utils/structs/stored-map.hpp"

FlashHashMap wifisConnected("wifis");

void WifiApp::ConnectToWifi()
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

        // Check if the network is open (no password required)
        bool isOpenNetwork = (WiFi.encryptionType(wifiIndex) == WIFI_AUTH_OPEN);

        String defaultPassword = wifisConnected.get(WiFi.SSID(wifiIndex)); // Optional default password
        String *password;
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

            // get password length
            CURSOR_OFFSET = defaultPassword.length() > 15 || defaultPassword.length() < 8 ? 15 : defaultPassword.length();
            // metadata
            password = input::ReadString({defaultPassword.length(), &defaultPassword}); // Read user input

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
                if (!isOpenNetwork)
                {
                    lcd.setCursor(0, 2);
                    lcd.print("Try to rewrite password!");
                }
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

        // store wifi passwor
        wifisConnected.set(WiFi.SSID(wifiIndex), isOpenNetwork ? "no pasword" : *password);

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
