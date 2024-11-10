#ifndef UTILS_STRUCTS_MWPL_HPP
#define UTILS_STRUCTS_MWPL_HPP

#include <Arduino.h> // Make sure to include Arduino library for String and Serial

/*
 * MWPL (Manuel Westermeier Protocol Location) URL Parsing
 *
 * Handles parsing of MWPL URLs with default values, such as:
 * - s: (secure) / us: (unsecure) prefix
 * - version (default to 1)
 * - host (required, cannot be empty)
 * - port (default 61680)
 * - route (default "")
 *
 * Example:
 * - "s:1:example.com#8080@home" -> secure, version 1, host=example.com, port=8080, route=home
 * - "example.com" -> unsecure, version 1, host=example.com, port=61680, route=""
 */

class MWPL
{
public:
    bool secure = false; // Secure flag, default is unsecure
    int version = 1;     // Default version
    String host;
    int port = 61680;  // Default port
    String route = ""; // Default route is empty

    MWPL() {}

    MWPL(const String &url)
    {
        parse(url);
    }

    void parse(const String &url)
    {
        if (url.length() == 0)
        {
            Serial.println("URL cannot be empty.");
            return;
        }

        size_t currentPos = 0;

        // Check secure prefix
        if (url.startsWith("s:"))
        {
            secure = true;
            currentPos = 2;
        }
        else if (url.startsWith("us:"))
        {
            secure = false;
            currentPos = 3;
        }

        // Check for optional version
        size_t nextColon = url.indexOf(':', currentPos);
        if (nextColon != -1 && nextColon < url.indexOf('@'))
        {
            version = url.substring(currentPos, nextColon).toInt();
            currentPos = nextColon + 1;
        }

        // Identify positions for host, port, and route
        size_t hostEnd = url.indexOf('#', currentPos);    // Position of '#'
        size_t routeStart = url.indexOf('@', currentPos); // Position of '@'

        if (hostEnd == -1 && routeStart == -1)
        {
            Serial.println("Invalid URL: Missing host.");
            return;
        }

        // Extract host (must be non-empty)
        host = url.substring(currentPos, hostEnd != -1 ? hostEnd : routeStart);
        if (host.length() == 0)
        {
            Serial.println("Invalid URL: Host cannot be empty.");
            return;
        }

        if (!isValidHost(host))
        {
            Serial.println("Invalid host format.");
            return;
        }

        // Extract port if present; otherwise default to 61680
        if (hostEnd != -1 && (routeStart == -1 || hostEnd < routeStart))
        {
            String portStr = url.substring(hostEnd + 1, routeStart != -1 ? routeStart : url.length());
            port = portStr.toInt();
            if (port < 1 || port > 65535)
            {
                Serial.println("Port out of valid range.");
                return;
            }
        }

        // Extract route if present; otherwise default to empty string
        if (routeStart != -1)
        {
            route = url.substring(routeStart + 1);
            if (!isValidRoute(route))
            {
                Serial.println("Invalid route format.");
                return;
            }
        }
    }

private:
    bool isValidHost(const String &host)
    {
        // Simple validation for valid hostname or IP
        for (size_t i = 0; i < host.length(); ++i)
        {
            char c = host[i];
            if (!isalnum(c) && c != '.' && c != '-')
            {
                return false;
            }
        }
        return true;
    }

    bool isValidRoute(const String &route)
    {
        // Allow alphanumeric and certain symbols in route
        for (size_t i = 0; i < route.length(); ++i)
        {
            char c = route[i];
            if (!isalnum(c) && c != '/' && c != '_' && c != '-')
            {
                return false;
            }
        }
        return true;
    }
};

#endif // UTILS_STRUCTS_MWPL_HPP