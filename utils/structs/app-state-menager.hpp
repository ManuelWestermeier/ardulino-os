#ifndef UTILS_STRUCTS_APP_STATE_MENAGER_HPP
#define UTILS_STRUCTS_APP_STATE_MENAGER_HPP

#include <map>
#include <vector>
#include <functional>
#include <string>

struct RoutePart
{
    bool isVariable = false;
    std::string value;

    RoutePart(const std::string &input)
    {
        if (!input.empty())
            isVariable = (input[0] == ':');
        value = input;
    }

    RoutePart(const std::string &input, bool _isVariable)
    {
        isVariable = _isVariable;
        value = input;
    }
};

// Type alias for route locations
using Location = std::vector<RoutePart>;

// Route callback type and "No Page" callback type
using RouteCallback = std::function<void(const std::map<std::string, std::string> &)>;
using NoPageCallback = std::function<void(const Location &)>;

struct Route
{
    Location route;
    RouteCallback routeCallback;

    Route(const Location &loc, RouteCallback callback)
        : route(loc), routeCallback(callback) {}
};

// Route matching operator
bool operator==(const Route &route, const Location &locationRoute)
{
    if (route.route.size() != locationRoute.size())
        return false;

    for (size_t i = 0; i < route.route.size(); ++i)
    {
        if (route.route[i].isVariable)
            continue; // Skip variable check
        if (route.route[i].value != locationRoute[i].value)
            return false; // Check static match
    }
    return true;
}

// Main AppStateManager struct
struct AppStateManager
{
    Location currentLocation;
    std::vector<Route> routes;
    NoPageCallback noPage;

    AppStateManager(Location root)
    {
        currentLocation = root;
    }

    AppStateManager(Location root, std::vector<Route> _routes)
    {
        routes = _routes;
        currentLocation = root;
    }

    AppStateManager(Location root, std::vector<Route> _routes, NoPageCallback _noPage)
    {
        routes = _routes;
        currentLocation = root;
        noPage = _noPage;
    }

    void Update()
    {
        for (const auto &route : routes)
        {
            if (route == currentLocation)
            {
                std::map<std::string, std::string> variables;

                // Extract variable values from the matched location
                for (size_t i = 0; i < route.route.size(); ++i)
                {
                    if (route.route[i].isVariable)
                    {
                        variables[route.route[i].value.substr(1)] = currentLocation[i].value;
                    }
                }

                // Call the matched route callback with the variables map
                route.routeCallback(variables);
                return;
            }
        }

        // If no route matches, call the "No Page" callback
        if (noPage)
        {
            noPage(currentLocation);
        }
    }

    void Navigate(Location newLocation)
    {
        currentLocation = newLocation;
        Update();
    }
};

#endif // UTILS_STRUCTS_APP_STATE_MENAGER_HPP

/**
#ifndef UTILS_STRUCTS_APP_STATE_MANAGER_HPP
#define UTILS_STRUCTS_APP_STATE_MANAGER_HPP

#include <Arduino.h> // For using String and functional callbacks

struct RoutePart
{
    bool isVariable = false;
    String value;

    RoutePart(const String &input)
    {
        if (input.length() > 0)
            isVariable = (input[0] == ':');
        value = input;
    }

    RoutePart(const String &input, bool _isVariable)
    {
        isVariable = _isVariable;
        value = input;
    }
};

// Type alias for route locations
using Location = std::vector<RoutePart>;

// Route callback type and "No Page" callback type
using RouteCallback = std::function<void(const std::map<String, String> &)>;
using NoPageCallback = std::function<void(const Location &)>;

struct Route
{
    Location route;
    RouteCallback routeCallback;

    Route(const Location &loc, RouteCallback callback)
        : route(loc), routeCallback(callback) {}
};

// Route matching operator
bool operator==(const Route &route, const Location &locationRoute)
{
    if (route.route.size() != locationRoute.size())
        return false;

    for (size_t i = 0; i < route.route.size(); ++i)
    {
        if (route.route[i].isVariable)
            continue; // Skip variable check
        if (route.route[i].value != locationRoute[i].value)
            return false; // Check static match
    }
    return true;
}

// Main AppStateManager struct
struct AppStateManager
{
    Location currentLocation;
    std::vector<Route> routes;
    NoPageCallback noPage;

    AppStateManager(Location root)
    {
        currentLocation = root;
    }

    AppStateManager(Location root, std::vector<Route> _routes)
    {
        routes = _routes;
        currentLocation = root;
    }

    AppStateManager(Location root, std::vector<Route> _routes, NoPageCallback _noPage)
    {
        routes = _routes;
        currentLocation = root;
        noPage = _noPage;
    }

    void Update()
    {
        for (const auto &route : routes)
        {
            if (route == currentLocation)
            {
                std::map<String, String> variables;

                // Extract variable values from the matched location
                for (size_t i = 0; i < route.route.size(); ++i)
                {
                    if (route.route[i].isVariable)
                    {
                        variables[route.route[i].value.substring(1)] = currentLocation[i].value;
                    }
                }

                // Call the matched route callback with the variables map
                route.routeCallback(variables);
                return;
            }
        }

        // If no route matches, call the "No Page" callback
        if (noPage)
        {
            noPage(currentLocation);
        }
    }

    void Navigate(Location newLocation)
    {
        currentLocation = newLocation;
        Update();
    }
};

#endif // UTILS_STRUCTS_APP_STATE_MANAGER_HPP
 */