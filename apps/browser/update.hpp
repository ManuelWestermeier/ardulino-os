#ifndef APPS_BROWSER_UPDATE_HPP
#define APPS_BROWSER_UPDATE_HPP

#include "../../globals.hpp"
#include "./index.hpp"

bool BrowserApp::WaitForConnected()
{
    static bool wasConnected;
    if (WiFi.status() != WL_CONNECTED)
    {
        // render ofline UI
        noWifiText.Draw();
        connectToWfifButton.Draw();
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
}

#endif