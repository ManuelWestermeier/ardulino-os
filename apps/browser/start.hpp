#ifndef APPS_BROWSER_START_HPP
#define APPS_BROWSER_START_HPP

#include "../../globals.hpp"
#include "../../utils/structs/mwpl.hpp"
#include "./index.hpp"

byte BrowserApp::Start(const String &url)
{
    Serial.println("Starting BrowserApp with URL: " + url);

    MWPL mwpl(url); // Attempt to parse the URL using the MWPL class

    if (mwpl.host.isEmpty())
    {
        Serial.println("Invalid URL: Missing host or invalid format");
        return 1; // Return error code if the URL is invalid
    }

    pages.Navigate({
        RoutePart("browser-view", false),           // browser-fiew
        RoutePart(mwpl.secure ? "s" : "us", false), // is secure
        RoutePart(String(mwpl.version), false),     // protocol version
        RoutePart(mwpl.host, false),                // host
        RoutePart(String(mwpl.port), false),        // port
        RoutePart(mwpl.route, false),               // route
    });

    Serial.println("Navigation started to route: " + mwpl.route);

    // Return a success status code (0)
    return 0;
}

#endif // APPS_BROWSER_START_HPP