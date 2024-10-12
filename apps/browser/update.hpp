#ifndef APPS_BROWSER_UPDATE_HPP
#define APPS_BROWSER_UPDATE_HPP

#include "../../globals.hpp"
#include "./index.hpp"

bool BrowserApp::WaitForConnected()
{
    static bool wasConnected;
    if (WiFi.status() != WL_CONNECTED)
    {
        // Render offline UI
        noWifiText.Draw();
        connectToWifiButton.Draw(); // Fixed typo here
        wasConnected = WiFi.status() != WL_CONNECTED;
        return false;
    }

    if (!wasConnected)
    {
        ClearAppScreen();
    }

    return true;
}

void BrowserApp::Update()
{
    SetAppTitle("Browser", 7);

    if (!WaitForConnected())
        return;

    if (State::appPage == Home) // Fixed appState to appPage here
    {
        goToViewInput.Draw();
    }
}

#endif