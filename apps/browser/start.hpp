#ifndef APPS_BROWSER_START_HPP
#define APPS_BROWSER_START_HPP

#include "../../globals.hpp"
#include "../../utils/structs/mwpl.hpp"
#include "./index.hpp"

byte BrowserApp::Start(const String &url)
{
    Serial.println("Starting BrowserApp with URL: " + url);

    // MWPL mwpl(url); // Attempt to parse the URL using the MWPL class

    // if (mwpl.host.isEmpty())
    // {
    //     Serial.println("Invalid URL: Missing host or invalid format");
    //     return 1; // Return error code if the URL is invalid
    // }

    // // If the URL is valid, initialize state or load the initial route
    // pages.Navigate({
    //     RoutePart("browser-view", false),
    //     RoutePart(String(mwpl.secure ? "s" : "us"), false), // Secure or unsecure
    //     RoutePart(String(mwpl.version), false),             // Version
    //     RoutePart(mwpl.host, false),                // Host
    //     RoutePart(String(mwpl.port), false),                // Port
    //     RoutePart(mwpl.route, false)                // Route
    // });

    // Serial.println("Navigation started to route: " + mwpl.route);

    // Return a success status code (0)
    return 0;
}

#endif // APPS_BROWSER_START_HPP